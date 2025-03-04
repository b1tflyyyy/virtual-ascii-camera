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

#include <mutex>
#include <memory>

template <typename TMat>
class DoubleBuffer
{
public:
    explicit DoubleBuffer(const std::size_t rows = 1, const std::size_t cols = 1) :
        mWriteMatrix{ std::make_unique<TMat>(rows, cols) }, mReadMatrix{ std::make_unique<TMat>(rows, cols) }, mMutex{}
    { }
    
    ~DoubleBuffer() noexcept = default;

    DoubleBuffer(const DoubleBuffer&) = delete;
    DoubleBuffer& operator=(const DoubleBuffer&) = delete;

    DoubleBuffer(DoubleBuffer&&) noexcept = delete;
    DoubleBuffer& operator=(DoubleBuffer&&) noexcept = delete;

    void Write(const TMat& input_matrix)
    {
        std::lock_guard<std::mutex> lk{ mMutex };
        
        input_matrix.copyTo(*mWriteMatrix);
        std::swap(mReadMatrix, mWriteMatrix);
    }

    void Read(TMat& output_buffer) const
    {
        std::lock_guard<std::mutex> lk{ mMutex };
        mReadMatrix->copyTo(output_buffer);
    }

private:
    std::unique_ptr<TMat> mWriteMatrix;
    std::unique_ptr<TMat> mReadMatrix;

    mutable std::mutex mMutex;
};