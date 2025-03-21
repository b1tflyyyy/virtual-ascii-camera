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

#include <QObject>

#include <v4l2-wrapper.hpp>

#include <common-device-model.hpp>

class VirtualCameraController : public QObject
{
    Q_OBJECT

public:
    explicit VirtualCameraController(CommonDeviceModel& virtual_camera_model, V4L2CXXWrapper& v4l2_cxx_wrapper, QObject* parent = nullptr);
    ~VirtualCameraController() noexcept override = default;

    // Connects to device 
    Q_INVOKABLE bool TryConnectToDevice(const QString& device);

    // Disconnects from device 
    Q_INVOKABLE bool TryDisconnectFromDevice();
    
    // Setup output video resolution
    Q_INVOKABLE bool SetupVideoResolution(const std::ptrdiff_t frame_width, const std::ptrdiff_t frame_height); 

private:
    CommonDeviceModel& mVirtualCameraModel;
    V4L2CXXWrapper& mV4L2CXXWrapper;
};
