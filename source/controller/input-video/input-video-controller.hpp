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

#include <optional>

#include <QObject>
#include <QDebug>

#include <opencv2/opencv.hpp>

#include <common-device-model.hpp>

class InputVideoController : public QObject
{
    Q_OBJECT

public:
    explicit InputVideoController(CommonDeviceModel& input_video_model, QObject* parent = nullptr);
    ~InputVideoController() noexcept override = default;

    // Tries to open the input source (realtime webcam or video (maybe in future))
    Q_INVOKABLE bool TryOpenInputSource(const QString& source_path);
    
    // Tries to close input source
    Q_INVOKABLE void CloseInputSource();

    // Returns grayscale frame
    [[nodiscard]] std::optional<cv::Mat1b*> GetFrame();

private:
    CommonDeviceModel& mInputVideoModel;

    cv::VideoCapture mVideoCapture;
    
    cv::Mat mOriginalFrame;
    cv::Mat1b mGrayscaleFrame;
};