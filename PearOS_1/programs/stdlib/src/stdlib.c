#include "stdlib.h"
#include "pearos.h"

char* itoa(int i)
{
    static char text[12];
    int loc = 11;
    text[11] = 0;
    char neg = 1;
    if (i >= 0)
    {
        neg = 0;
        i = -i;
    }

    while(i)
    {
        text[--loc] = '0' - (i % 10);
        i /= 10;
    }

    if (loc == 11)
    {
        text[--loc] = '0';
    }
    if (neg)
    {
        text[--loc] = '-';
    }

    return &text[loc];
}

void* malloc(size_t size)
{
    return pearos_malloc(size);
}

void free(void* ptr)
{
    return pearos_free(ptr);
}
