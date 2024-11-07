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

    return 0;
}