#ifndef STRUCT
#define STRUCT
#define SIZE 4096
#define COUNT 8192

#include <stdint.h>

struct buffer{
    volatile uint64_t position;
    volatile int array[COUNT][SIZE];
};

#endif
