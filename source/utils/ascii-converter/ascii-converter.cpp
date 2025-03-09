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
    mOutputFrame{}, mLookupTable(256) 
{ 
    createLookupTable();
}

// TODO: maybe add more input parameters and parallelize it ?
cv::Mat2b& ASCIIConverter::ProcessInputFrame(cv::Mat1b& input_frame)
{
    const auto original_cols{ static_cast<std::ptrdiff_t>(input_frame.cols) };
    const auto original_rows{ static_cast<std::ptrdiff_t>(input_frame.rows) };

    // resize by symbol dimension 
    cv::resize(input_frame, input_frame, cv::Size(original_cols / SYMBOL_DIMENSION, original_rows / SYMBOL_DIMENSION));
    mOutputFrame = cv::Mat2b(original_rows, original_cols, cv::Vec2b{ 0, 128 });

    for (std::ptrdiff_t resized_i{}; resized_i < input_frame.rows; ++resized_i) 
    {
        for (std::ptrdiff_t resized_j{}; resized_j < input_frame.cols; ++resized_j) 
        {
            const auto pixel_value{ static_cast<std::ptrdiff_t>(input_frame[resized_i][resized_j]) };
            const mat8x8_t& symbol_representation{ mLookupTable[pixel_value] };

            for (std::ptrdiff_t symbol_i{}; symbol_i < static_cast<std::ptrdiff_t>(SYMBOL_DIMENSION); ++symbol_i)
            {
                for (std::ptrdiff_t symbol_j{}; symbol_j < static_cast<std::ptrdiff_t>(SYMBOL_DIMENSION); symbol_j += 2) // += 2 'cause work with 2 pixels in 1 iteration
                {
                    cv::Vec2b& yuyv_1{ mOutputFrame.at<cv::Vec2b>(resized_i * SYMBOL_DIMENSION + symbol_i, resized_j * SYMBOL_DIMENSION + symbol_j) };
                    cv::Vec2b& yuyv_2{ mOutputFrame.at<cv::Vec2b>(resized_i * SYMBOL_DIMENSION + symbol_i, resized_j * SYMBOL_DIMENSION + symbol_j + 1) };

                    // set level of white
                    yuyv_1[0] = symbol_representation[symbol_i][symbol_j];
                    yuyv_2[0] = symbol_representation[symbol_i][symbol_j + 1];
                
                    // set neutral Cb Cr
                    yuyv_1[1] = 128;
                    yuyv_2[1] = 128;
                }
            }
        }
    }

    return mOutputFrame;
}

void ASCIIConverter::createLookupTable()
{   
    for (std::size_t i{}; i < 256; ++i)
    {
        const auto new_idx{ mapValue(i, 0, 255, 0, std::size(SYMBOL_REPRESENTATIONS) - 1) };
        mLookupTable[i] = SYMBOL_REPRESENTATIONS[new_idx];
    }    
}

std::size_t ASCIIConverter::mapValue(const float old_value, const float old_min, const float old_max, const float new_min, const float new_max)
{
    return static_cast<std::size_t>(((old_value - old_min) / (old_max - old_min)) * (new_max - new_min) + new_min);
}