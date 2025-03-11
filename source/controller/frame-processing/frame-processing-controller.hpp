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

#pragma once

#include <thread>
#include <optional>

#include <QObject>

#include <ascii-converter.hpp>
#include <v4l2-wrapper.hpp>
#include <input-video-controller.hpp>
#include <double-buffer.hpp>
#include <frame-processing-model.hpp>

class FrameProcessingController : public QObject
{
    Q_OBJECT

public:
    explicit FrameProcessingController(InputVideoController& input_video_controller, ASCIIConverter& ascii_converter, V4L2CXXWrapper& v4l2_cxx_wrapper, FrameProcessingModel& frame_processing_model, QObject* parent = nullptr);
    ~FrameProcessingController() noexcept override;

    Q_INVOKABLE void StartBroadcasting();
    Q_INVOKABLE void StopBroadcasting();

private:
    void processingFrame(std::stop_token stop_token);
    void virtualCameraBroadcasting(std::stop_token stop_token);

    void stopProcessingThread() noexcept;
    void stopBroadcastingThread() noexcept;

private:
    InputVideoController& mInputVideoController;
    ASCIIConverter& mASCIIConverter;
    V4L2CXXWrapper& mV4L2CXXWrapper;
    FrameProcessingModel& mFrameProcessingModel;
    
    std::optional<std::jthread> mProcessingThread;
    std::optional<std::jthread> mBroadcastingThread;

    DoubleBuffer<cv::Mat2b> mDoubleBuffer;
};