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

/*
    Place for ASCII convertor testing :)
    ...
*/

#include <ascii-converter.hpp>
#include <double-buffer.hpp>

#include <thread>

int main()
{
    DoubleBuffer<cv::Mat1b> dbuff{};

    auto f = [&dbuff]() -> void 
    {
        cv::VideoCapture vc{};
        vc.open("/dev/video0");

        if (!vc.isOpened())
        {
            std::cerr << "err open\n";
        }

        ASCIIConverter cvrt{};
    
        std::vector<std::string> symbols
        {
            ".", "-", "=", "*", ":", "o", "&", "8", "#", "@"
        };

        cvrt.SetASCIISymbols(std::move(symbols));

        cv::Mat original{};
        cv::Mat1b converted{};

        for (;;)
        {
            vc.read(original);
            cv::cvtColor(original, converted, cv::COLOR_BGR2GRAY);

            const auto& processed{ cvrt.ProcessInputFrame(converted) };
            dbuff.Write(processed);
        };
    };

    std::thread th{ std::move(f) };

    cv::Mat1b res{};
    for (;;)
    {
        dbuff.Read(res);
        cv::imshow("test", res);

        cv::waitKey(1);
    }

    th.join();

    return 0;
}