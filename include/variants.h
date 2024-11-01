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
#include "variants.core.h"

INLINE_VARIANT_TYPE(void*)
INLINE_VARIANT_TYPE(bool)
INLINE_VARIANT_TYPE(char)
INLINE_VARIANT_TYPE(float)
INLINE_VARIANT_TYPE(double)
INLINE_VARIANT_TYPE(int8_t)
INLINE_VARIANT_TYPE(int16_t)
INLINE_VARIANT_TYPE(int32_t)
INLINE_VARIANT_TYPE(int64_t)
INLINE_VARIANT_TYPE(decltype(nullptr))
INLINE_VARIANT_TYPE(uint8_t)
INLINE_VARIANT_TYPE(uint16_t)
INLINE_VARIANT_TYPE(uint32_t)
INLINE_VARIANT_TYPE(uint64_t)

namespace variant
{
    constexpr int8_t VALUE_TYPE_NONE = 0x00;
    constexpr int8_t VALUE_TYPE_I008 = 0x01;
    constexpr int8_t VALUE_TYPE_I016 = 0x02;
    constexpr int8_t VALUE_TYPE_I032 = 0x03;
    constexpr int8_t VALUE_TYPE_I064 = 0x04;
    constexpr int8_t VALUE_TYPE_U008 = 0x05;
    constexpr int8_t VALUE_TYPE_U016 = 0x06;
    constexpr int8_t VALUE_TYPE_U032 = 0x07;
    constexpr int8_t VALUE_TYPE_U064 = 0x08;
    constexpr int8_t VALUE_TYPE_F032 = 0x09;
    constexpr int8_t VALUE_TYPE_F064 = 0x10;
    constexpr int8_t VALUE_TYPE_BLOB = 0x11;

    template<class type> struct decoder<type*> {
        inline static void run(value const & src, type* & dst) {
            return decoder<void*>::run(src, (void * &)dst);
        }
    };

    template<class type> struct encoder<type*> {
        inline static void run(type* const & src, value & dst) {
            return encoder<void*>::run((void * const &)src, dst);
        }
    };

    template<class type> constexpr bool is_value<type*> = is_value<type>;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(void*)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = nullptr;  return;
        case VALUE_TYPE_I008: dst = nullptr;  return;
        case VALUE_TYPE_I016: dst = nullptr;  return;
        case VALUE_TYPE_I032: dst = nullptr;  return;
        case VALUE_TYPE_I064: dst = nullptr;  return;
        case VALUE_TYPE_U008: dst = nullptr;  return;
        case VALUE_TYPE_U016: dst = nullptr;  return;
        case VALUE_TYPE_U032: dst = nullptr;  return;
        case VALUE_TYPE_U064: dst = nullptr;  return;
        case VALUE_TYPE_F032: dst = nullptr;  return;
        case VALUE_TYPE_F064: dst = nullptr;  return;
        case VALUE_TYPE_BLOB: dst = src.blob; return;
        default:              dst = nullptr;  return;
    }
}

INLINE_VARIANT_ENCODER(void*)
{
    dst.size = 0;
    dst.blob = src;
    dst.type = VALUE_TYPE_BLOB;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(bool)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = false;    return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = src.blob; return;
        default:              dst = false;    return;
    }
}

INLINE_VARIANT_ENCODER(bool)
{
    dst.size = 0;
    dst.i008 = src;
    dst.type = VALUE_TYPE_I008;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(char)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(char)
{
    dst.size = 0;
    dst.i008 = src;
    dst.type = VALUE_TYPE_I008;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(float)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0.0f;     return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0.0f;     return;
        default:              dst = 0.0f;     return;
    }
}

INLINE_VARIANT_ENCODER(float)
{
    dst.size = 0;
    dst.f032 = src;
    dst.type = VALUE_TYPE_F032;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(double)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0.0;      return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0.0;      return;
        default:              dst = 0.0;      return;
    }
}

INLINE_VARIANT_ENCODER(double)
{
    dst.size = 0;
    dst.f064 = src;
    dst.type = VALUE_TYPE_F064;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(int8_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(int8_t)
{
    dst.size = 0;
    dst.i008 = src;
    dst.type = VALUE_TYPE_I008;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(int16_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(int16_t)
{
    dst.size = 0;
    dst.i016 = src;
    dst.type = VALUE_TYPE_I016;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(int32_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(int32_t)
{
    dst.size = 0;
    dst.i032 = src;
    dst.type = VALUE_TYPE_I032;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(int64_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(int64_t)
{
    dst.size = 0;
    dst.i064 = src;
    dst.type = VALUE_TYPE_I064;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(decltype(nullptr))
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = nullptr; return;
        case VALUE_TYPE_I008: dst = nullptr; return;
        case VALUE_TYPE_I016: dst = nullptr; return;
        case VALUE_TYPE_I032: dst = nullptr; return;
        case VALUE_TYPE_I064: dst = nullptr; return;
        case VALUE_TYPE_U008: dst = nullptr; return;
        case VALUE_TYPE_U016: dst = nullptr; return;
        case VALUE_TYPE_U032: dst = nullptr; return;
        case VALUE_TYPE_U064: dst = nullptr; return;
        case VALUE_TYPE_F032: dst = nullptr; return;
        case VALUE_TYPE_F064: dst = nullptr; return;
        case VALUE_TYPE_BLOB: dst = nullptr; return;
        default:              dst = nullptr; return;
    }
}

INLINE_VARIANT_ENCODER(decltype(nullptr))
{
    dst.size = 0;
    dst.blob = nullptr;
    dst.type = VALUE_TYPE_BLOB;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(uint8_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(uint8_t)
{
    dst.size = 0;
    dst.u008 = src;
    dst.type = VALUE_TYPE_U008;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(uint16_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(uint16_t)
{
    dst.size = 0;
    dst.u016 = src;
    dst.type = VALUE_TYPE_U016;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(uint32_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(uint32_t)
{
    dst.size = 0;
    dst.u032 = src;
    dst.type = VALUE_TYPE_U032;
}

// -------------------------------------------------------------------------------------------------------------------------- //

INLINE_VARIANT_DECODER(uint64_t)
{
    switch (src.type)
    {
        case VALUE_TYPE_NONE: dst = 0;        return;
        case VALUE_TYPE_I008: dst = src.i008; return;
        case VALUE_TYPE_I016: dst = src.i016; return;
        case VALUE_TYPE_I032: dst = src.i032; return;
        case VALUE_TYPE_I064: dst = src.i064; return;
        case VALUE_TYPE_U008: dst = src.u008; return;
        case VALUE_TYPE_U016: dst = src.u016; return;
        case VALUE_TYPE_U032: dst = src.u032; return;
        case VALUE_TYPE_U064: dst = src.u064; return;
        case VALUE_TYPE_F032: dst = src.f032; return;
        case VALUE_TYPE_F064: dst = src.f064; return;
        case VALUE_TYPE_BLOB: dst = 0;        return;
        default:              dst = 0;        return;
    }
}

INLINE_VARIANT_ENCODER(uint64_t)
{
    dst.size = 0;
    dst.u064 = src;
    dst.type = VALUE_TYPE_U064;
}

// -------------------------------------------------------------------------------------------------------------------------- //