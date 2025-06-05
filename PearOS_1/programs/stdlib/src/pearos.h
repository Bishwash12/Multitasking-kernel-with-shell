#ifndef PEAROS_H
#define PEAROS_H
#include <stddef.h>
#include <stdbool.h>

void print(const char* message);
int pearos_getkey();
void* pearos_malloc(size_t size);
void pearos_free(void* ptr);
void pearos_putchar(char c);
int pearos_getkeyblock();
void pearos_terminal_readline(char* out, int max, bool output_while_typing);

#endif