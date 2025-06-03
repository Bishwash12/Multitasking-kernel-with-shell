#include "stdlib.h"
#include "pearos.h"

void* malloc(size_t size)
{
    return pearos_malloc(size);
}

void free(void* ptrdiff_t)
{
    
}
