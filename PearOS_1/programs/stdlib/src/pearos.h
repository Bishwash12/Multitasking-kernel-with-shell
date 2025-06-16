#ifndef PEAROS_H
#define PEAROS_H
#include <stddef.h>
#include <stdbool.h>

struct command_argument
{
    char argument[512];
    struct command_argument* next;
};

struct process_arguments
{
    int argc;
    char** argv;
};

struct command_argument* pearos_parse_command(const char* command, int max);

void print(const char* message);
int pearos_getkey();
void* pearos_malloc(size_t size);
void pearos_free(void* ptr);
void pearos_putchar(char c);
int pearos_getkeyblock();
void pearos_terminal_readline(char* out, int max, bool output_while_typing);
void pearos_process_load_start(const char* filename);
void pearos_process_get_arguments(struct process_arguments* arguments);
int pearos_system(struct command_argument* arguments);
int pearos_system_run(const char* command);
#endif