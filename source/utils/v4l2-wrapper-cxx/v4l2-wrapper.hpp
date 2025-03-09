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

#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstdint>
#include <string>

class V4L2CXXWrapper
{
public:
    using v4l2_format_t = struct v4l2_format;

    V4L2CXXWrapper() :
        mFileDescriptor{ -1 }
    { }

    ~V4L2CXXWrapper() noexcept
    {
        (void) TryCloseDevice();
    }

    [[nodiscard]] bool TryOpenDevice(std::string_view device)
    {
        mFileDescriptor = open(std::data(device), O_WRONLY);
        return !(mFileDescriptor < 0);   
    }

    [[nodiscard]] bool TryCloseDevice() noexcept
    {
        if (mFileDescriptor < 0)
        {
            return false;
        }

        close(mFileDescriptor);
        mFileDescriptor = -1;

        return true;
    }

    [[nodiscard]] bool TrySetupDeviceFormat(const v4l2_format_t& format)
    {
        return !(ioctl(mFileDescriptor, VIDIOC_S_FMT, &format) < 0);
    }

    template <typename TMat>
    [[nodiscard]] bool TryWriteFrame(const TMat& frame)
    {
        return !(write(mFileDescriptor, frame.data, frame.total() * frame.elemSize()) < 0);
    }

private:
    std::int32_t mFileDescriptor;
};