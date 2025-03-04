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

#include "ascii-converter.hpp"

ASCIIConverter::ASCIIConverter() :
    mOutputFrame{}, mLookupTable(256), mASCIISymbols{} // 256 -> from 0 to 255
{ }

void ASCIIConverter::SetASCIISymbols(std::vector<std::string>&& ascii_symbols) 
{
    mASCIISymbols = std::move(ascii_symbols);
    createLookupTable();
}

// TODO: maybe add more input parameters and parallelize it ?
cv::Mat1b& ASCIIConverter::ProcessInputFrame(cv::Mat1b& input_frame)
{
    // Original params from the input frame
    const auto original_cols{ input_frame.cols };
    const auto original_rows{ input_frame.rows };

    // Definiton of dimension of single symbol -> 8 x 8 pixels
    const std::int32_t dimension{ 8 };

    // Resize input frame by dimension
    cv::resize(input_frame, input_frame, cv::Size{ original_cols / dimension, input_frame.rows / dimension });

    // Init out frame
    mOutputFrame = cv::Mat1b::zeros(original_rows, original_cols);

    // ...
    constexpr std::size_t horizontal_space{ 2 };
    constexpr std::size_t vertical_space{ 8 };

    for (std::size_t i{}; i < static_cast<std::size_t>(input_frame.rows); ++i)
    {
        uchar* ptr{ input_frame.ptr(i) };

        for (std::size_t j{}; j < static_cast<std::size_t>(input_frame.cols); ++j)
        {
            const auto idx{ static_cast<std::size_t>(ptr[j]) };
            const auto& symbol{ mLookupTable[idx] };

            cv::putText(mOutputFrame, symbol, cv::Point(j * dimension + horizontal_space, i * dimension + vertical_space), cv::FONT_HERSHEY_SIMPLEX, 0.4, cv::Scalar::all(255), 1, cv::LINE_8, false);
        }
    }

    return mOutputFrame;
}

void ASCIIConverter::createLookupTable()
{   
    for (std::size_t i{}; i < 256; ++i)
    {
        const auto new_idx{ mapValue(i, 0, 255, 0, std::size(mASCIISymbols) - 1) };
        mLookupTable[i] = mASCIISymbols[new_idx];
    }    
}

std::size_t ASCIIConverter::mapValue(const float old_value, const float old_min, const float old_max, const float new_min, const float new_max)
{
    return static_cast<std::size_t>(((old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min);
}