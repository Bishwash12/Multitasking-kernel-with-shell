#ifndef PEAROS_STDLIB_H
#define PEAROS_STDLIB_H
#include <stddef.h>

char* itoa(int i);
void* malloc(size_t size);
void free(void* ptr);
#endif