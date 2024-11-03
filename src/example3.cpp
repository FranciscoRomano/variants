namespace variant
{
    template<class type> struct dispose;
    template<> struct dispose<void> {
        inline static void run(struct value const & src);
    };
}

#include <string>
#include <iostream>
#include <variants.h>

namespace variant
{
    constexpr uint8_t VALUE_TYPE_CSTR = 0x12;
};
INLINE_VARIANT_TYPE(std::string)

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
    dst.size = src.size() + 1;
    dst.type = VALUE_TYPE_CSTR;
    dst.blob = malloc(dst.size);
    memcpy(dst.blob, &src[0], dst.size);
}

void variant::dispose<void>::run(struct value const & src)
{
    printf("Running custom dispose system");
    if (src.type == VALUE_TYPE_CSTR && src.blob)
    {
        free(src.blob);
    }
}

int main()
{
    {
        std::string line = "This message is still valid inside a variant";
        variant::value value = line;
        std::string result = (std::string)value;

        printf("Decoding message...\n\n%s\n", &result[0]);
    }

    return 0;
}