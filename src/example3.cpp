#include <string>
#include <stdlib.h>
#include <iostream>
#define VARIANT_ALLOCATOR
#include <variants.h>

constexpr uint8_t VALUE_TYPE_CSTR = 0x12;

INLINE_VARIANT_DECODER(std::string)
{
    switch (src.type)
    {
        case VALUE_TYPE_CSTR:
            dst.resize(src.size);
            memcpy(&dst[0], src.blob, src.size);
            return;
        default:
            dst = std::string("ERROR");
            return;
    }
}

INLINE_VARIANT_ENCODER(std::string)
{
    dst.type = VALUE_TYPE_CSTR;
    variant::alloc(dst, src.size() + 1);
    memcpy(dst.blob, &src[0], dst.size);
}

inline static void variant::free(value & src)
{
    printf("releasing memory...\n");
    if (src.size) ::free(src.blob);
    src.size = 0;
}

inline static void variant::alloc(value & src, size_t const & size)
{
    printf("allocating memory...\n");
    src.blob = src.size ? ::realloc(src.blob, size) : ::malloc(size);
    src.size = size;
}

int main()
{
    std::string line = "This message is still valid inside a variant";
    variant::value value = line;
    std::string result = (std::string)value;

    printf("Decoding message...\n\n%s\n", &result[0]);

    return 0;
}