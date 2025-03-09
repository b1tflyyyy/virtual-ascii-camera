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

#include "input-video-controller.hpp"

InputVideoController::InputVideoController(CommonDeviceModel& input_video_model, QObject* parent) :
    QObject{ parent }, mInputVideoModel{ input_video_model }, mVideoCapture{}, mOriginalFrame{}, mGrayscaleFrame{}
{ }

bool InputVideoController::TryOpenInputSource(const QString& source_path)
{
    if (source_path.isEmpty())
    {
        return false;
    }

    const auto& std_string{ source_path.toStdString() };    
    const auto result{ mVideoCapture.open(std_string) };    

    mInputVideoModel.SetConnectionStatus(result);
    
    return result;
}

void InputVideoController::CloseInputSource()
{
    mVideoCapture.release();
    mInputVideoModel.SetConnectionStatus(false);
}

cv::Mat1b& InputVideoController::GetFrame()
{
    mVideoCapture.read(mOriginalFrame);
    cv::cvtColor(mOriginalFrame, mGrayscaleFrame, cv::COLOR_BGR2GRAY);

    return mGrayscaleFrame;
}