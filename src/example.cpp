#include <stdio.h>
#include <variants.h>

int main(int argc, char** argv)
{
    variant::value values[] = {
        true,
        (int8_t)-34,
        (int16_t)-3434,
        (int32_t)-343434,
        (int64_t)-34343434,
        (uint8_t)34,
        (uint16_t)3434,
        (uint32_t)343434,
        (uint64_t)34343434,
        1.236273f,
        2.4372842834723536263,
        argv[0],
        (void*)0,
        nullptr
    };

    printf("[ 0] - %s\n",              (bool)values[ 0] ? "true" : "false");
    printf("[ 1] - %i\n",            (int8_t)values[ 1]);
    printf("[ 2] - %i\n",           (int16_t)values[ 2]);
    printf("[ 3] - %i\n",           (int32_t)values[ 3]);
    printf("[ 4] - %i\n",           (int64_t)values[ 4]);
    printf("[ 5] - %i\n",           (uint8_t)values[ 5]);
    printf("[ 6] - %i\n",          (uint16_t)values[ 6]);
    printf("[ 7] - %i\n",          (uint32_t)values[ 7]);
    printf("[ 8] - %i\n",          (uint64_t)values[ 8]);
    printf("[ 9] - %f\n",             (float)values[ 9]);
    printf("[10] - %f\n",            (double)values[10]);
    printf("[11] - %s\n",             (char*)values[11]);
    printf("[12] - %i\n",             (void*)values[12]);
    printf("[13] - %i\n", (decltype(nullptr))values[13]);

    return 0;
}