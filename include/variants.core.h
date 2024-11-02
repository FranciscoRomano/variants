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
#include <stdint.h>

#define INLINE_VARIANT_TYPE(...)\
namespace variant {\
    template<> constexpr bool is_value<__VA_ARGS__> = true;\
    template<> struct encoder<__VA_ARGS__> {\
        static void run(__VA_ARGS__ const & src, value & dst);\
    };\
    template<> struct decoder<__VA_ARGS__> {\
        static void run(value const & src, __VA_ARGS__ & dst);\
    };\
};
#define INLINE_VARIANT_DECODER(...)\
inline void variant::decoder<__VA_ARGS__>::run(variant::value const & src, __VA_ARGS__ & dst)
#define INLINE_VARIANT_ENCODER(...)\
inline void variant::encoder<__VA_ARGS__>::run(__VA_ARGS__ const & src, variant::value & dst)

namespace variant {

    /// Represents a decoder that converts values to C++ types.
    template<class type> struct decoder {
        inline static void run(struct value const & src, type & dst) {}
    };

    /// Represents a encoder that converts C++ types to values.
    template<class type> struct encoder {
        inline static void run(type const & src, struct value & dst) {}
    };

    /// Evaluates to true if the specified C++ type is a value.
    template<class type> constexpr bool is_value = false;

    /// Represents a union-based container for all value types.
    struct value final {
        int8_t       type; // The stored value type.
        int64_t      size; // The allocated memory size.
        union {
            int8_t   i008; // A 8-bit signed integer type.
            int16_t  i016; // A 16-bit signed integer type.
            int32_t  i032; // A 32-bit signed integer type.
            int64_t  i064; // A 64-bit signed integer type.
            uint8_t  u008; // A 8-bit unsigned integer type.
            uint16_t u016; // A 16-bit unsigned integer type.
            uint32_t u032; // A 32-bit unsigned integer type.
            uint64_t u064; // A 64-bit unsigned integer type.
            float    f032; // A 32-bit floating-point type.
            double   f064; // A 64-bit floating-point type.
            void*    blob; // A incomplete type that points to memory.
        };
        value() = default;
        template<class type> requires(is_value<type>) operator type() {
            type dst;
            decoder<type>::run(*this, dst);
            return (type&&)dst;
        }
        template<class type> requires(is_value<type>) value(type const & src) {
            encoder<type>::run(src, *this);
        }
    };
}

// -------------------------------------------------------------------------------------------------------------------------- //