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

#include <atomic>

class FrameProcessingModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ProcessingState broadcastingState READ GetBroadcastingState NOTIFY broadcastingStateChanged)

public:
    enum class ProcessingState : std::uint8_t
    {
        BROADCASTING,
        WAITING,
    };

    Q_ENUM(ProcessingState)

public:
    explicit FrameProcessingModel(QObject* parent = nullptr);
    ~FrameProcessingModel() noexcept override = default;

    void SetBroadcastingState(ProcessingState state);
    ProcessingState GetBroadcastingState() const noexcept;

signals:
    void broadcastingStateChanged();

    void inputDeviceError();
    void outputDeviceError();

private:
    std::atomic<ProcessingState> mBroadcastingState;
};