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
#include <stdlib.h>
#include <string.h>

constexpr int8_t VARIANT_TYPE_NONE = 0x00; // A incomplete/empty type.
constexpr int8_t VARIANT_TYPE_I008 = 0x01; // A 8-bit signed integer type.
constexpr int8_t VARIANT_TYPE_I016 = 0x02; // A 16-bit signed integer type.
constexpr int8_t VARIANT_TYPE_I032 = 0x03; // A 32-bit signed integer type.
constexpr int8_t VARIANT_TYPE_I064 = 0x04; // A 64-bit signed integer type.
constexpr int8_t VARIANT_TYPE_U008 = 0x05; // A 8-bit unsigned integer type.
constexpr int8_t VARIANT_TYPE_U016 = 0x06; // A 16-bit unsigned integer type.
constexpr int8_t VARIANT_TYPE_U032 = 0x07; // A 32-bit unsigned integer type.
constexpr int8_t VARIANT_TYPE_U064 = 0x08; // A 64-bit unsigned integer type.
constexpr int8_t VARIANT_TYPE_F032 = 0x09; // A 32-bit floating-point type.
constexpr int8_t VARIANT_TYPE_F064 = 0x10; // A 64-bit floating-point type.
constexpr int8_t VARIANT_TYPE_BLOB = 0x11; // A type that points to memory.

namespace variant {
    /// Represents a collection of memory management functions.
    struct memory {
        static void free(struct value & src);
        static void init(struct value & src, size_t size);
        static void swap(struct value & src, struct value & other);
        static void copy(struct value & src, struct value const & other);
    };

    /// Represents a decoder that converts values to C++ types.
    template<class type> struct decoder {
        inline static constexpr bool exists = false;
        inline static void run(struct value const & src, type & dst) {}
    };

    /// Represents a encoder that converts C++ types to values.
    template<class type> struct encoder {
        inline static constexpr bool exists = false;
        inline static void run(type const & src, struct value & dst) {}
    };

    /// Represents a union-based container for all value types.
    struct value {
        size_t       size = 0;
        int8_t       type = 0;
        union {
            int8_t   i008;
            int16_t  i016;
            int32_t  i032;
            int64_t  i064;
            uint8_t  u008;
            uint16_t u016;
            uint32_t u032;
            uint64_t u064;
            float    f032;
            double   f064;
            void*    blob;
        };
        value() = default;
        ~value() { memory::free(*this); }
        value(value && src) { memory::swap(*this, src); }
        value(value const & src) { memory::copy(*this, src); }
        void operator=(value && src) { memory::swap(*this, src); }
        void operator=(value const & src) { memory::copy(*this, src); }
        template<class type> requires(decoder<type>::exists) operator type() {
            type dst;
            decoder<type>::run(*this, dst);
            return (type&&)dst;
        }
        template<class type> requires(encoder<type>::exists) value(type const & src) {
            encoder<type>::run(src, *this);
        }
    };
}
// -------------------------------------------------------------------------------------------------------------------------- //
#ifndef WITHOUT_VARIANT_DECODERS

template<> struct variant::decoder<bool> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, bool & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = false;    return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = src.blob; return;
            default:                dst = false;    return;
        }
    }
};

template<> struct variant::decoder<char> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, char & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<int8_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, int8_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<int16_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, int16_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<int32_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, int32_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<int64_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, int64_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<uint8_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, uint8_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<uint16_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, uint16_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<uint32_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, uint32_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<uint64_t> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, uint64_t & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0;        return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0;        return;
            default:                dst = 0;        return;
        }
    }
};

template<> struct variant::decoder<float> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, float & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0.0f;     return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0.0f;     return;
            default:                dst = 0.0f;     return;
        }
    }
};

template<> struct variant::decoder<double> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, double & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = 0.0;      return;
            case VARIANT_TYPE_I008: dst = src.i008; return;
            case VARIANT_TYPE_I016: dst = src.i016; return;
            case VARIANT_TYPE_I032: dst = src.i032; return;
            case VARIANT_TYPE_I064: dst = src.i064; return;
            case VARIANT_TYPE_U008: dst = src.u008; return;
            case VARIANT_TYPE_U016: dst = src.u016; return;
            case VARIANT_TYPE_U032: dst = src.u032; return;
            case VARIANT_TYPE_U064: dst = src.u064; return;
            case VARIANT_TYPE_F032: dst = src.f032; return;
            case VARIANT_TYPE_F064: dst = src.f064; return;
            case VARIANT_TYPE_BLOB: dst = 0.0;      return;
            default:                dst = 0.0;      return;
        }
    }
};

template<> struct variant::decoder<void*> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, void* & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = nullptr;  return;
            case VARIANT_TYPE_I008: dst = nullptr;  return;
            case VARIANT_TYPE_I016: dst = nullptr;  return;
            case VARIANT_TYPE_I032: dst = nullptr;  return;
            case VARIANT_TYPE_I064: dst = nullptr;  return;
            case VARIANT_TYPE_U008: dst = nullptr;  return;
            case VARIANT_TYPE_U016: dst = nullptr;  return;
            case VARIANT_TYPE_U032: dst = nullptr;  return;
            case VARIANT_TYPE_U064: dst = nullptr;  return;
            case VARIANT_TYPE_F032: dst = nullptr;  return;
            case VARIANT_TYPE_F064: dst = nullptr;  return;
            case VARIANT_TYPE_BLOB: dst = src.blob; return;
            default:                dst = nullptr;  return;
        }
    }
};

template<> struct variant::decoder<decltype(nullptr)> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, decltype(nullptr) & dst) {
        switch (src.type) {
            case VARIANT_TYPE_NONE: dst = nullptr; return;
            case VARIANT_TYPE_I008: dst = nullptr; return;
            case VARIANT_TYPE_I016: dst = nullptr; return;
            case VARIANT_TYPE_I032: dst = nullptr; return;
            case VARIANT_TYPE_I064: dst = nullptr; return;
            case VARIANT_TYPE_U008: dst = nullptr; return;
            case VARIANT_TYPE_U016: dst = nullptr; return;
            case VARIANT_TYPE_U032: dst = nullptr; return;
            case VARIANT_TYPE_U064: dst = nullptr; return;
            case VARIANT_TYPE_F032: dst = nullptr; return;
            case VARIANT_TYPE_F064: dst = nullptr; return;
            case VARIANT_TYPE_BLOB: dst = nullptr; return;
            default:                dst = nullptr; return;
        }
    }
};

template<class type> struct variant::decoder<type*> {
    inline static constexpr bool exists = true;
    inline static void run(value const & src, type* & dst) {
        return variant::decoder<void*>::run(src, (void* &)dst);
    }
};

#endif//WITHOUT_VARIANT_DECODERS
// -------------------------------------------------------------------------------------------------------------------------- //
#ifndef WITHOUT_VARIANT_ENCODERS

template<> struct variant::encoder<bool> {
    inline static constexpr bool exists = true;
    inline static void run(bool const & src, value & dst) {
        dst.size = 0;
        dst.i008 = src;
        dst.type = VARIANT_TYPE_I008;
    }
};

template<> struct variant::encoder<char> {
    inline static constexpr bool exists = true;
    inline static void run(char const & src, value & dst) {
        dst.size = 0;
        dst.i008 = src;
        dst.type = VARIANT_TYPE_I008;
    }
};

template<> struct variant::encoder<int8_t> {
    inline static constexpr bool exists = true;
    inline static void run(int8_t const & src, value & dst) {
        dst.size = 0;
        dst.i008 = src;
        dst.type = VARIANT_TYPE_I008;
    }
};

template<> struct variant::encoder<int16_t> {
    inline static constexpr bool exists = true;
    inline static void run(int16_t const & src, value & dst) {
        dst.size = 0;
        dst.i016 = src;
        dst.type = VARIANT_TYPE_I016;
    }
};

template<> struct variant::encoder<int32_t> {
    inline static constexpr bool exists = true;
    inline static void run(int32_t const & src, value & dst) {
        dst.size = 0;
        dst.i032 = src;
        dst.type = VARIANT_TYPE_I032;
    }
};

template<> struct variant::encoder<int64_t> {
    inline static constexpr bool exists = true;
    inline static void run(int64_t const & src, value & dst) {
        dst.size = 0;
        dst.i064 = src;
        dst.type = VARIANT_TYPE_I064;
    }
};

template<> struct variant::encoder<uint8_t> {
    inline static constexpr bool exists = true;
    inline static void run(uint8_t const & src, value & dst) {
        dst.size = 0;
        dst.u008 = src;
        dst.type = VARIANT_TYPE_U008;
    }
};

template<> struct variant::encoder<uint16_t> {
    inline static constexpr bool exists = true;
    inline static void run(uint16_t const & src, value & dst) {
        dst.size = 0;
        dst.u016 = src;
        dst.type = VARIANT_TYPE_U016;
    }
};

template<> struct variant::encoder<uint32_t> {
    inline static constexpr bool exists = true;
    inline static void run(uint32_t const & src, value & dst) {
        dst.size = 0;
        dst.u032 = src;
        dst.type = VARIANT_TYPE_U032;
    }
};

template<> struct variant::encoder<uint64_t> {
    inline static constexpr bool exists = true;
    inline static void run(uint64_t const & src, value & dst) {
        dst.size = 0;
        dst.u064 = src;
        dst.type = VARIANT_TYPE_U064;
    }
};

template<> struct variant::encoder<float> {
    inline static constexpr bool exists = true;
    inline static void run(float const & src, value & dst) {
        dst.size = 0;
        dst.f032 = src;
        dst.type = VARIANT_TYPE_F032;
    }
};

template<> struct variant::encoder<double> {
    inline static constexpr bool exists = true;
    inline static void run(double const & src, value & dst) {
        dst.size = 0;
        dst.f064 = src;
        dst.type = VARIANT_TYPE_F064;
    }
};

template<> struct variant::encoder<void*> {
    inline static constexpr bool exists = true;
    inline static void run(void* const & src, value & dst) {
        dst.size = 0;
        dst.blob = src;
        dst.type = VARIANT_TYPE_BLOB;
    }
};

template<> struct variant::encoder<decltype(nullptr)> {
    inline static constexpr bool exists = true;
    inline static void run(decltype(nullptr) const & src, value & dst) {
        dst.size = 0;
        dst.blob = nullptr;
        dst.type = VARIANT_TYPE_BLOB;
    }
};

template<class type> struct variant::encoder<type*> {
    inline static constexpr bool exists = true;
    inline static void run(type* const & src, value & dst) {
        return variant::encoder<void*>::run((void* const &)src, dst);
    }
};

#endif//WITHOUT_VARIANT_ENCODERS
// -------------------------------------------------------------------------------------------------------------------------- //
#ifndef WITHOUT_VARIANT_ALLOCATOR

inline void variant::memory::free(value & src) {
    if (src.size) ::free(src.blob);
    src.size = 0;
}

inline void variant::memory::init(value & src, size_t size) {
    src.blob = size ? src.size ? ::realloc(src.blob, size) : ::malloc(size) : nullptr;
    src.size = size;
}

inline void variant::memory::swap(value & src, value & other) {
    { size_t t = src.size; src.size = other.size; other.size = t; }
    { int8_t t = src.type; src.type = other.type; other.type = t; }
    { void*  t = src.blob; src.blob = other.blob; other.blob = t; }
}

inline void variant::memory::copy(value & src, value const & other) {
    if (src.size) ::free(src.blob);
    src.size = other.size;
    src.type = other.type;
    if (other.size) {
        variant::memory::init(src, other.size);
        ::memcpy(src.blob, other.blob, other.size);
    } else src.u064 = other.u064;
}

#endif//WITHOUT_VARIANT_ALLOCATOR
// -------------------------------------------------------------------------------------------------------------------------- //
#define INLINE_VARIANT_ENCODER(...)\
template<> struct variant::encoder<__VA_ARGS__> {\
    inline static constexpr bool exists = true;\
    inline static void run(__VA_ARGS__ const & src, value & dst);\
};\
inline void variant::encoder<__VA_ARGS__>::run(__VA_ARGS__ const & src, value & dst)
// -------------------------------------------------------------------------------------------------------------------------- //
#define INLINE_VARIANT_DECODER(...)\
template<> struct variant::decoder<__VA_ARGS__> {\
    inline static constexpr bool exists = true;\
    inline static void run(value const & src, __VA_ARGS__ & dst);\
};\
inline void variant::decoder<__VA_ARGS__>::run(value const & src, __VA_ARGS__ & dst)
// -------------------------------------------------------------------------------------------------------------------------- //