#include <variants.h>
#include <stdexcept>
#include <format>

#ifndef _WIN32
#include <unistd.h>
#define PLATFORM_SLEEP sleep(0)
#else
#define PLATFORM_SLEEP
#endif

#define ASSERT(Condition, ...)\
if (!(Condition)) { throw std::runtime_error(std::format(__VA_ARGS__)); }

#define ARE_EQUAL(A, B)\
ASSERT((A) == (B), "Failed Assert: " #A " == " #B)

#define ASSERT_VARIANT(Size, Type)\
for (int i = 0; i < 10000; i++)\
{\
    auto v = (Type)(rand() % VARIANT_MAXV_##Type);\
    variant::value t = v;\
    if (t.size                 != Size                  ) throw std::runtime_error("Failed Assert: " #Type " size");\
    if (t.VARIANT_NAME_##Type  != (VARIANT_CAST_##Type)v) throw std::runtime_error("Failed Assert: " #Type " data");\
    if (t.type                 != VARIANT_ENUM_##Type   ) throw std::runtime_error("Failed Assert: " #Type " type");\
    if ((VARIANT_CAST_##Type)t != v                     ) throw std::runtime_error("Failed Assert: " #Type " cast");\
    PLATFORM_SLEEP;\
}

#define VARIANT_NAME_bool i008
#define VARIANT_CAST_bool int8_t
#define VARIANT_ENUM_bool VARIANT_TYPE_I008
#define VARIANT_MAXV_bool 2

#define VARIANT_NAME_char i008
#define VARIANT_CAST_char int8_t
#define VARIANT_ENUM_char VARIANT_TYPE_I008
#define VARIANT_MAXV_char 255

#define VARIANT_NAME_int8_t i008
#define VARIANT_CAST_int8_t int8_t
#define VARIANT_ENUM_int8_t VARIANT_TYPE_I008
#define VARIANT_MAXV_int8_t INT8_MAX

#define VARIANT_NAME_int16_t i016
#define VARIANT_CAST_int16_t int16_t
#define VARIANT_ENUM_int16_t VARIANT_TYPE_I016
#define VARIANT_MAXV_int16_t INT16_MAX

#define VARIANT_NAME_int32_t i032
#define VARIANT_CAST_int32_t int32_t
#define VARIANT_ENUM_int32_t VARIANT_TYPE_I032
#define VARIANT_MAXV_int32_t INT32_MAX

#define VARIANT_NAME_int64_t i064
#define VARIANT_CAST_int64_t int64_t
#define VARIANT_ENUM_int64_t VARIANT_TYPE_I064
#define VARIANT_MAXV_int64_t INT64_MAX

#define VARIANT_NAME_uint8_t u008
#define VARIANT_CAST_uint8_t uint8_t
#define VARIANT_ENUM_uint8_t VARIANT_TYPE_U008
#define VARIANT_MAXV_uint8_t UINT8_MAX

#define VARIANT_NAME_uint16_t u016
#define VARIANT_CAST_uint16_t uint16_t
#define VARIANT_ENUM_uint16_t VARIANT_TYPE_U016
#define VARIANT_MAXV_uint16_t UINT16_MAX

#define VARIANT_NAME_uint32_t u032
#define VARIANT_CAST_uint32_t uint32_t
#define VARIANT_ENUM_uint32_t VARIANT_TYPE_U032
#define VARIANT_MAXV_uint32_t UINT32_MAX

#define VARIANT_NAME_uint64_t u064
#define VARIANT_CAST_uint64_t uint64_t
#define VARIANT_ENUM_uint64_t VARIANT_TYPE_U064
#define VARIANT_MAXV_uint64_t UINT64_MAX

struct Assert {
    template<class type>
    static void AreEqual(type a, variant::value b)
    {
        if (a != (type)b) throw std::runtime_error("Failed 'Assert.AreEqual'");
    }
    template<class type>
    static void AreEqual(variant::value a, type b)
    {
        if ((type)a != b) throw std::runtime_error("Failed 'Assert.AreEqual'");
    }
};

int main(int argc, char** argv)
{
    // check 'bool' constructor
    ASSERT_VARIANT(0, bool)

    // check 'char' constructor
    ASSERT_VARIANT(0, char);

    // check 'int8_t' constructor
    ASSERT_VARIANT(0, int8_t);

    // check 'int16_t' constructor
    ASSERT_VARIANT(0, int16_t);

    // check 'int32_t' constructor
    ASSERT_VARIANT(0, int32_t);

    // check 'int64_t' constructor
    ASSERT_VARIANT(0, int64_t);

    // check 'uint8_t' constructor
    ASSERT_VARIANT(0, uint8_t);

    // check 'uint16_t' constructor
    ASSERT_VARIANT(0, uint16_t);

    // check 'int32_t' constructor
    ASSERT_VARIANT(0, int32_t);

    // check 'int64_t' constructor
    ASSERT_VARIANT(0, int64_t);

    variant::value values[] = {
        true,
        (int8_t)-34,
        (int16_t)-3434,
        (int32_t)-34343434,
        (int64_t)-3434343434343434,
        (uint8_t)34,
        (uint16_t)3434,
        (uint32_t)34343434,
        (uint64_t)3434343434343434,
        34567.0f,
        3456789.0,
        argv[0],
        (void*)0,
        nullptr
    };
    Assert::AreEqual(values[0x0], true);
    Assert::AreEqual(values[0x1], true);
    Assert::AreEqual(values[0x2], true);
    Assert::AreEqual(values[0x3], true);
    Assert::AreEqual(values[0x4], true);
    Assert::AreEqual(values[0x5], true);
    Assert::AreEqual(values[0x6], true);
    Assert::AreEqual(values[0x7], true);
    Assert::AreEqual(values[0x8], true);
    Assert::AreEqual(values[0x9], true);
    Assert::AreEqual(values[0xA], true);
    Assert::AreEqual(values[0xB], true);
    Assert::AreEqual(values[0xC], false);
    Assert::AreEqual(values[0xD], false);

    Assert::AreEqual(values[0x0], 1);
    Assert::AreEqual(values[0x1], -34);
    Assert::AreEqual(values[0x2], -3434);
    Assert::AreEqual(values[0x3], -34343434);
    Assert::AreEqual(values[0x4], -3434343434343434);
    Assert::AreEqual(values[0x5], 34);
    Assert::AreEqual(values[0x6], 3434);
    Assert::AreEqual(values[0x7], 34343434);
    Assert::AreEqual(values[0x8], 3434343434343434);
    Assert::AreEqual(values[0x9], 34567);
    Assert::AreEqual(values[0xA], 3456789);

    return 0;
}