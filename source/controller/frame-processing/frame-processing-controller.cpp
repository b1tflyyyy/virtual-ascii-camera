// MIT License
// 
// Copyright (c) 2025 @Who
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "frame-processing-controller.hpp"

FrameProcessingController::FrameProcessingController(InputVideoController& input_video_controller, ASCIIConverter& ascii_converter, V4L2CXXWrapper& v4l2_cxx_wrapper, FrameProcessingModel& frame_processing_model, QObject* parent) :                         /* ------- set neutral level -------*/
    QObject{ parent }, mInputVideoController{ input_video_controller }, mASCIIConverter{ ascii_converter }, mV4L2CXXWrapper{ v4l2_cxx_wrapper }, mFrameProcessingModel{ frame_processing_model }, mProcessingThread{}, mBroadcastingThread{}, mDoubleBuffer{}, mCbLevel{ 128 }, mCrLevel{ 128 }
{ }

FrameProcessingController::~FrameProcessingController() noexcept 
{
    stopProcessingThread();
    stopBroadcastingThread();
}

void FrameProcessingController::SetCbLevel(const uchar cb)
{
    mCbLevel.store(cb, std::memory_order_relaxed);
}

void FrameProcessingController::SetCrLevel(const uchar cr)
{
    mCrLevel.store(cr, std::memory_order_relaxed);
}

void FrameProcessingController::StartBroadcasting()
{
    if (!mProcessingThread.has_value() && !mBroadcastingThread.has_value())
    {
        mFrameProcessingModel.SetBroadcastingState(FrameProcessingModel::ProcessingState::BROADCASTING);

        mProcessingThread.emplace(&FrameProcessingController::processingFrame, this);
        mBroadcastingThread.emplace(&FrameProcessingController::virtualCameraBroadcasting, this);
    }
}

void FrameProcessingController::StopBroadcasting()
{
    stopProcessingThread();
    stopBroadcastingThread();

    mFrameProcessingModel.SetBroadcastingState(FrameProcessingModel::ProcessingState::WAITING);
}

void FrameProcessingController::processingFrame(std::stop_token stop_token)
{
    while (!stop_token.stop_requested())
    {
        auto grayscale_frame{ mInputVideoController.GetFrame() };
        if (!grayscale_frame.has_value())
        {
            emit mFrameProcessingModel.inputDeviceError();
            return;
        }

        const auto cr{ mCrLevel.load(std::memory_order_relaxed) };
        const auto cb{ mCbLevel.load(std::memory_order_relaxed) };

        const cv::Mat2b& processed_frame{ mASCIIConverter.ProcessInputFrame(*grayscale_frame.value(), cr, cb) };
        mDoubleBuffer.Write(processed_frame);
    }
}

void FrameProcessingController::virtualCameraBroadcasting(std::stop_token stop_token)
{
    cv::Mat2b output_frame{};

    while (!stop_token.stop_requested())
    {
        mDoubleBuffer.Read(output_frame);
        if (!mV4L2CXXWrapper.TryWriteFrame(output_frame))
        {
            emit mFrameProcessingModel.outputDeviceError();
            return;
        }
    }
}

void FrameProcessingController::stopProcessingThread() noexcept
{
    if (mProcessingThread.has_value())
    {
        mProcessingThread->request_stop();
        mProcessingThread.reset();
    }
}

void FrameProcessingController::stopBroadcastingThread() noexcept
{
    if (mBroadcastingThread.has_value())
    {
        mBroadcastingThread->request_stop();
        mBroadcastingThread.reset();
    }
}