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

#include "virtual-camera-controller.hpp"

VirtualCameraController::VirtualCameraController(VirtualCameraModel& virtual_camera_model, QObject* parent) :
    QObject{ parent }, mVirtualCameraModel{ virtual_camera_model }, mV4L2CXXWrapper{ }
{ }

bool VirtualCameraController::TryConnectToDevice(const QString& device)
{
    const auto& std_string{ device.toStdString() };
    const auto result{ mV4L2CXXWrapper.TryOpenDevice(std_string) };
    
    mVirtualCameraModel.SetConnectionStatus(result);
    return result;
}

bool VirtualCameraController::TryDisconnectFromDevice()
{
    const auto result{ mV4L2CXXWrapper.TryCloseDevice() };

    mVirtualCameraModel.SetConnectionStatus(!result); // if success, set connection status to false
    return result;
}

bool VirtualCameraController::SetupVideoFormat(const std::int32_t frame_width, const std::int32_t frame_height)
{
    V4L2CXXWrapper::v4l2_format_t format{};

    format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

    format.fmt.pix.width = frame_width;
    format.fmt.pix.height = frame_height;

    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    format.fmt.pix.field = V4L2_FIELD_NONE;

    return mV4L2CXXWrapper.TrySetupDeviceFormat(format);
}