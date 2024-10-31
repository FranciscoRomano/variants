// -------------------------------------------------------------------------------------------------------------------------- //
// The MIT License (MIT)
// 
// Copyright (c) 2024 Francisco Romano
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
// -------------------------------------------------------------------------------------------------------------------------- //
#pragma once
#include "variants.h"
#include <stdio.h>

template<>
struct VariantSerializer<double>
{
    inline static constexpr bool IsSupported = true;
    inline static bool Decode(const Variant& src, std::add_lvalue_reference_t<double> dst)
    {
        switch (src.Type)
        {
            case VariantType::Void:                            return false;
            case VariantType::Null:                            return false;
            case VariantType::Bool:    dst = src.Data.Bool;    return true;
            case VariantType::Int8:    dst = src.Data.Int8;    return true;
            case VariantType::Int16:   dst = src.Data.Int16;   return true;
            case VariantType::Int32:   dst = src.Data.Int32;   return true;
            case VariantType::Int64:   dst = src.Data.Int64;   return true;
            case VariantType::Uint8:   dst = src.Data.Uint8;   return true;
            case VariantType::Uint16:  dst = src.Data.Uint16;  return true;
            case VariantType::Uint32:  dst = src.Data.Uint32;  return true;
            case VariantType::Uint64:  dst = src.Data.Uint64;  return true;
            case VariantType::Float32: dst = src.Data.Float32; return true;
            case VariantType::Float64: dst = src.Data.Float64; return true;
            case VariantType::Pointer:                         return false;
            default:                                           return false;
        }
    }
    inline static bool Encode(const std::add_lvalue_reference_t<double> src, Variant& dst)
    {
        dst.Type = VariantType::Float32;
        dst.Data.Float32 = src;
        return true;
    }
};