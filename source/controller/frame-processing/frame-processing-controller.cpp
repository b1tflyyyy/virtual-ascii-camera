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

FrameProcessingController::FrameProcessingController(InputVideoController& input_video_controller, ASCIIConverter& ascii_converter, V4L2CXXWrapper& v4l2_cxx_wrapper, QObject* parent) : 
    QObject{ parent }, mInputVideoController{ input_video_controller }, mASCIIConverter{ ascii_converter }, mV4L2CXXWrapper{ v4l2_cxx_wrapper }, mProcessingThread{}, mBroadcastingThread{}, mDoubleBuffer{}
{ }

void FrameProcessingController::StartBroadcasting()
{
    if (!mProcessingThread.has_value() && !mBroadcastingThread.has_value())
    {
        mProcessingThread.emplace(&FrameProcessingController::processingFrame, this);
        mBroadcastingThread.emplace(&FrameProcessingController::virtualCameraBroadcasting, this);
    }

    if (mProcessingThread->joinable() && mBroadcastingThread->joinable())
    {
        mProcessingThread->detach();
        mBroadcastingThread->detach();
    }
}

// TODO: add this to the UI
void FrameProcessingController::StopBroadcasting()
{
    mProcessingThread->request_stop();
    mBroadcastingThread->request_stop();
}

void FrameProcessingController::processingFrame(std::stop_token stop_token)
{
    while (!stop_token.stop_requested())
    {
        cv::Mat1b& grayscale_frame{ mInputVideoController.GetFrame() };
        const cv::Mat2b& processed_frame{ mASCIIConverter.ProcessInputFrame(grayscale_frame) };

        mDoubleBuffer.Write(processed_frame);
    }
}

// TODO: handle "Error writing frame"
void FrameProcessingController::virtualCameraBroadcasting(std::stop_token stop_token)
{
    cv::Mat2b output_frame{};

    while (!stop_token.stop_requested())
    {
        mDoubleBuffer.Read(output_frame);
        if (!mV4L2CXXWrapper.TryWriteFrame(output_frame))
        {
            std::cerr << "Error writing frame\n";
            return;
        }
    }
}