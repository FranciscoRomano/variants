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

template<>
struct VariantSerializer<void*>
{
    inline static constexpr bool IsSupported = true;
    inline static bool Decode(const Variant& src, std::add_lvalue_reference_t<void*> dst)
    {
        switch (src.Type)
        {
            case VariantType::Void:                            return false;
            case VariantType::Null:                            return false;
            case VariantType::Bool:                            return false;
            case VariantType::Int8:                            return false;
            case VariantType::Int16:                           return false;
            case VariantType::Int32:                           return false;
            case VariantType::Int64:                           return false;
            case VariantType::Uint8:                           return false;
            case VariantType::Uint16:                          return false;
            case VariantType::Uint32:                          return false;
            case VariantType::Uint64:                          return false;
            case VariantType::Float32:                         return false;
            case VariantType::Float64:                         return false;
            case VariantType::Pointer: dst = src.Data.Pointer; return false;
            default:                                           return false;
        }
    }
    inline static bool Encode(const std::add_lvalue_reference_t<void*> src, Variant& dst)
    {
        dst.Type = VariantType::Pointer;
        dst.Data.Pointer = src;
        return true;
    }
};

template<class Type>
struct VariantSerializer<Type*>
{
    inline static constexpr bool IsSupported = VariantSerializer<Type>::IsSupported;
    inline static bool Decode(const Variant& src, std::add_lvalue_reference_t<Type*> dst)
    {
        switch (src.Type)
        {
            case VariantType::Void:                                   return false;
            case VariantType::Null:                                   return false;
            case VariantType::Bool:                                   return false;
            case VariantType::Int8:                                   return false;
            case VariantType::Int16:                                  return false;
            case VariantType::Int32:                                  return false;
            case VariantType::Int64:                                  return false;
            case VariantType::Uint8:                                  return false;
            case VariantType::Uint16:                                 return false;
            case VariantType::Uint32:                                 return false;
            case VariantType::Uint64:                                 return false;
            case VariantType::Float32:                                return false;
            case VariantType::Float64:                                return false;
            case VariantType::Pointer: dst = (Type*)src.Data.Pointer; return false;
            default:                                                  return false;
        }
    }
    inline static bool Encode(const std::add_lvalue_reference_t<Type*> src, Variant& dst)
    {
        dst.Type = VariantType::Pointer;
        dst.Data.Pointer = src;
        return true;
    }
};