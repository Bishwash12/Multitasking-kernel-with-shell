#ifndef PEAROS_H
#define PEAROS_H
#include <stddef.h>

void print(const char* message);
int getkey();
void* pearos_malloc(size_t size);
void pearos_free(void* ptr);
void putchar(char c);
#endif