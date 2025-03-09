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

#include <array>

#include <opencv2/core/hal/interface.h>

// TODO: add namespace

constexpr std::size_t SYMBOL_DIMENSION{ 8 }; // -> 8 x 8

using mat8x8_t = std::array<std::array<uchar, SYMBOL_DIMENSION>, SYMBOL_DIMENSION>;

constexpr mat8x8_t DOT_REPRESENTATION
{
    {
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  255,  255,  0,  0,  0 },
        {0,  0,  0,  255,  255,  0,  0,  0 },
    },
};

constexpr mat8x8_t DASH_REPRESENTATION
{
    {
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
    }
};

constexpr mat8x8_t EQUALS_REPRESENTATION
{
    {
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {100,  255,  255,  255,  255,  255,  255,  100 },
        {0,  0,  0,  0,  0,  0,  0,  0 },
    }
};

constexpr mat8x8_t STAR_REPRESENTATION
{
    {
        {  0,  0,  0, 50, 50,  0,  0,  0 },
        {  0,  0, 50,200,200, 50,  0,  0 },
        {  0, 50,200,200,200,200, 50,  0 },
        { 50,200,200,200,200,200,200, 50 },
        {  0, 50,200,200,200,200, 50,  0 },
        {  0,  0, 50,200,200, 50,  0,  0 },
        {  0,  0,  0, 50, 50,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0,  0,  0 },
    }
};

constexpr mat8x8_t COLON_REPRESENTATION
{
    {
        {  0,  0,  0,  0,  0,  0,  0,  0 },
        {  0,  0,  0,128,128,  0,  0,  0 },
        {  0,  0,  0,128,128,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0,  0,  0 },
        {  0,  0,  0,128,128,  0,  0,  0 },
        {  0,  0,  0,128,128,  0,  0,  0 },
        {  0,  0,  0,  0,  0,  0,  0,  0 },
    }
};

constexpr mat8x8_t O_REPRESENTATION
{
    {
        {  0,  0, 50,200,200, 50,  0,  0 },
        {  0, 50,200,200,200,200, 50,  0 },
        { 50,200,200,  0,  0,200,200, 50 },
        { 50,200,  0,  0,  0,  0,200, 50 },
        { 50,200,  0,  0,  0,  0,200, 50 },
        { 50,200,200,  0,  0,200,200, 50 },
        {  0, 50,200,200,200,200, 50,  0 },
        {  0,  0, 50,200,200, 50,  0,  0 },
    }
};

constexpr mat8x8_t AMPERSAND_REPRESENTATION
{
    {
        {  0, 50,200,200,200, 50,  0,  0 },
        { 50,200,200,200,200,200, 50,  0 },
        { 50,200,200, 50,200,200,200, 50 },
        {  0, 50,200,200,200,200,200, 50 },
        {  0, 50,200,200,200,200,200, 50 },
        { 50,200,200,200,200,200,200, 50 },
        { 50,200,200,200,200,200,200, 50 },
        {  0, 50, 50, 50, 50, 50, 50,  0 },
    }
};

constexpr mat8x8_t HASH_REPRESENTATION
{
    {
        { 50,200, 50,200, 50,200, 50,200 },
        { 50,200, 50,200, 50,200, 50,200 },
        { 50,200, 50,200, 50,200, 50,200 },
        {200,200,200,200,200,200,200,200 },
        {200,200,200,200,200,200,200,200 },
        { 50,200, 50,200, 50,200, 50,200 },
        { 50,200, 50,200, 50,200, 50,200 },
        { 50,200, 50,200, 50,200, 50,200 },
    }
};

constexpr mat8x8_t AT_REPRESENTATION
{
    {
        {  0,  50,200,200,200, 50,  0,  0 },
        { 50,200,200, 50, 50,200,200, 50 },
        {200,200, 50,200,200, 50,200,200 },
        {200,200,200,200,200, 50,200,200 },
        {200,200,200,200,200, 50,200,200 },
        {200,200, 50,200,200,200,200, 50 },
        { 50,200,200, 50, 50,200,200, 50 },
        {  0,  50,200,200,200, 50,  0,  0 },
    }
};

constexpr std::array<mat8x8_t, 9> SYMBOL_REPRESENTATIONS
{
    DOT_REPRESENTATION,
    DASH_REPRESENTATION,
    EQUALS_REPRESENTATION,
    STAR_REPRESENTATION,
    COLON_REPRESENTATION,
    O_REPRESENTATION,
    AMPERSAND_REPRESENTATION,
    HASH_REPRESENTATION,
    AT_REPRESENTATION,
};