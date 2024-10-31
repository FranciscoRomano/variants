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
#include <type_traits>

struct Variant;

/// Represents all fundamental types supported by a variant.
enum class VariantType : uint8_t {
    Void    = 0x00, // A incomplete/empty type.
    Null    = 0x01, // A null type.
    Bool    = 0x02, // A integer type that is 'true' or 'false'.
    Int8    = 0x03, // A 8-bit signed integer type.
    Int16   = 0x04, // A 16-bit signed integer type.
    Int32   = 0x05, // A 32-bit signed integer type.
    Int64   = 0x06, // A 64-bit signed integer type.
    Uint8   = 0x07, // A 8-bit unsigned integer type.
    Uint16  = 0x08, // A 16-bit unsigned integer type.
    Uint32  = 0x09, // A 32-bit unsigned integer type.
    Uint64  = 0x0A, // A 64-bit unsigned integer type.
    Float32 = 0x0B, // A 32-bit floating-point type.
    Float64 = 0x0C, // A 64-bit floating-point type.
    Pointer = 0x10, // A integer type that points to a value or address.
};

/// Represents all fundamental values supported by a variant.
union VariantValue final {
    bool      Bool;    // A integer type that is 'true' or 'false'.
    int8_t    Int8;    // A 8-bit signed integer type.
    int16_t   Int16;   // A 16-bit signed integer type.
    int32_t   Int32;   // A 32-bit signed integer type.
    int64_t   Int64;   // A 64-bit signed integer type.
    uint8_t   Uint8;   // A 8-bit unsigned integer type.
    uint16_t  Uint16;  // A 16-bit unsigned integer type.
    uint32_t  Uint32;  // A 32-bit unsigned integer type.
    uint64_t  Uint64;  // A 64-bit unsigned integer type.
    float     Float32; // A 32-bit floating-point type.
    double    Float64; // A 64-bit floating-point type.
    void*     Pointer; // A integer type that points to a value or address.
};

/// Represents a variant serializer for decoding and encoding values.
template<class Type>
struct VariantSerializer {
    /// 'true' if the variant serializer is supported.
    inline static constexpr bool IsSupported = false;
    /// Returns true if the value was decoded successfully.
    static bool Decode(const Variant& src, std::add_lvalue_reference_t<Type> dst) { return false; }
    /// Returns true if the value was encoded successfully.
    static bool Encode(const std::add_lvalue_reference_t<Type> src, Variant& dst) { return false; }
};

/// Declares a new supported type for encoding and decoding as a variant.
#define DECLARE_VARIANT_TYPE(...)\
template<> struct VariantSerializer<__VA_ARGS__> {\
    inline static constexpr bool IsSupported = true;\
    static bool Decode(const Variant& src, std::add_lvalue_reference_t<__VA_ARGS__> dst);\
    static bool Encode(const std::add_lvalue_reference_t<__VA_ARGS__> src, Variant& dst);\
};

/// Declares a custom 'Decode' function, after using `DECLARE_VARIANT_TYPE`.
#define DECLARE_VARIANT_DECODER(...)\
bool VariantSerializer<__VA_ARGS__>::Decode(const Variant& src, std::add_lvalue_reference_t<__VA_ARGS__> dst)

/// Declares a custom 'Encode' function, after using `DECLARE_VARIANT_TYPE`.
#define DECLARE_VARIANT_ENCODER(...)\
bool VariantSerializer<__VA_ARGS__>::Encode(const std::add_lvalue_reference_t<__VA_ARGS__> src, Variant& dst)

/// Represents a union-based varying container for all declared variant types.
struct Variant final {
    /// Creates a zero-initialized variant.
    Variant() = default;
    /// Returns the implicit conversion of a value to a new variant.
    template<typename Type> requires(VariantSerializer<Type>::IsSupported)
    Variant(Type src) { VariantSerializer<Type>::Encode(src, *this); }
    /// Returns the implicit conversion of the variant to a new value.
    template<typename Type> requires(VariantSerializer<Type>::IsSupported)
    operator Type() const { Type dst; VariantSerializer<Type>::Decode(*this, dst); return dst; }
protected:
    template<class Type> friend struct VariantSerializer;
    VariantType  Type = VariantType::Void; // A enum representing the variant type.
    VariantValue Data = {};                // A union containing the value of the variant.
};