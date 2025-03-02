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
#include <vector>
#include <cstddef>

class V4L2CXXWrapper
{
public:
    using frame_t = std::vector<std::byte>;
    using v4l2_format_t = struct v4l2_format;

    V4L2CXXWrapper();
    ~V4L2CXXWrapper() noexcept;

    [[nodiscard]] bool TryOpenDevice(std::string_view device);
    [[nodiscard]] bool TryCloseDevice() noexcept;

    [[nodiscard]] bool TrySetupDeviceFormat(const v4l2_format_t& format);

    [[nodiscard]] bool TryWriteFrame(const frame_t& frame);

private:
    std::int32_t mFileDescriptor;
};