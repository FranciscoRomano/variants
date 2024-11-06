#define WITHOUT_VARIANT_ALLOCATOR
#include <variants.h>
#include <string>
#include <stdlib.h>
#include <string.h>

constexpr uint8_t VARIANT_TYPE_CSTR = 0x12;

INLINE_VARIANT_DECODER(std::string)
{
    switch (src.type)
    {
        case VARIANT_TYPE_CSTR:
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
    dst.type = VARIANT_TYPE_CSTR;
    variant::memory::init(dst, src.size() + 1);
    memcpy(dst.blob, &src[0], dst.size);
}

inline void variant::memory::free(value & src) {
    printf("calling 'variant::memory::free'...\n");
    if (src.size) ::free(src.blob);
    src.size = 0;
}

inline void variant::memory::init(value & src, size_t size) {
    printf("calling 'variant::memory::init'...\n");
    src.blob = size ? src.size ? ::realloc(src.blob, size) : ::malloc(size) : nullptr;
    src.size = size;
}

inline void variant::memory::swap(value & src, value & other) {
    printf("calling 'variant::memory::swap'...\n");
    { size_t t = src.size; src.size = other.size; other.size = t; }
    { int8_t t = src.type; src.type = other.type; other.type = t; }
    { void*  t = src.blob; src.blob = other.blob; other.blob = t; }
}

inline void variant::memory::copy(value & src, value const & other) {
    printf("calling 'variant::memory::copy'...\n");
    if (src.size) ::free(src.blob);
    src.size = other.size;
    src.type = other.type;
    if (other.size) {
        variant::memory::init(src, other.size);
        ::memcpy(src.blob, other.blob, other.size);
    } else src.u064 = other.u064;
}

int main()
{
    std::string line = "This message is still valid inside a variant";
    variant::value value = line;
    std::string result = (std::string)value;

    printf("Decoding message...\n\n%s\n", &result[0]);

    return 0;
}