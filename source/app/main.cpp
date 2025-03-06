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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <common-device-model.hpp>

#include <virtual-camera-controller.hpp>
#include <input-video-controller.hpp>

int main(int argc, char** argv)
{
    QGuiApplication app{ argc, argv };
    QQmlApplicationEngine engine{};

    auto* ctx{ engine.rootContext() };

    CommonDeviceModel virtual_camera_model{};
    VirtualCameraController virtual_camera_controller{ virtual_camera_model };
    
    CommonDeviceModel input_video_model{};
    InputVideoController input_video_controller{ input_video_model };

    ctx->setContextProperty("virtualCameraModel", &virtual_camera_model);
    ctx->setContextProperty("virtualCameraController", &virtual_camera_controller);

    ctx->setContextProperty("inputVideoModel", &input_video_model);
    ctx->setContextProperty("inputVideoController", &input_video_controller);

    const QUrl& url{ QStringLiteral("qrc:/main-window/MainWindow.qml") };
    engine.load(url);

    return QGuiApplication::exec();
}