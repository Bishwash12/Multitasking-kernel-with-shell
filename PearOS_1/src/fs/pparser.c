#include "pparser.h"
#include "kernel.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "memory/memory.h"

static int path_valid_formate(const char* filename)
{
    int len = strnlen(filename, PEAROS_MAX_PATH);
    return (len >= 3 && isdigit(filename[0]) && memcmp((void*)&filename[1], ":/", 2) == 0);

}