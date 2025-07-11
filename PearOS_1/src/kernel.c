#include "kernel.h"
#include <stdint.h>
#include <stddef.h>
#include "idt/idt.h"
#include "io/io.h"
#include "memory/heap/kheap.h"
#include "memory/paging/paging.h"
#include "string/string.h"
#include "disk/disk.h"
#include "fs/pparser.h"
#include "disk/streamer.h"
#include "gdt/gdt.h"
#include "task/tss.h"
#include "config.h"
#include "memory/memory.h"
#include "task/task.h"
#include "task/process.h"
#include "status.h"
#include "isr80h/isr80h.h"
#include "keyboard/keyboard.h"

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;
uint16_t terminal_col = 0;

uint16_t terminal_make_char(char c, char colour)
{
    return (colour << 8) | c;
}

void terminal_putchar(int x, int y, char c, char colour)
{
    video_mem[(y * VGA_WIDTH) + x] = terminal_make_char(c, colour);
}

void terminal_backspace()
{
    if (terminal_row == 0 && terminal_col == 0)
    {
        return;
    }

    if (terminal_col == 0)
    {
        terminal_row -= 1;
        terminal_col = VGA_WIDTH;
    }

    terminal_col -= 1;
    terminal_writechar(' ', 15);
    terminal_col -= 1;
}

void terminal_writechar(char c, char colour)
{
    if (c == '\n')
    {
        terminal_row += 1;
        terminal_col = 0;
        return;
    }

    if (c == 0x08)
    {
        terminal_backspace();
        return;
    }

    terminal_putchar(terminal_col, terminal_row, c, colour);
    terminal_col += 1;
    if (terminal_col >= VGA_WIDTH)
    {
        terminal_col = 0;
        terminal_row += 1;
    }
}

void terminal_initialize()
{
    video_mem = (uint16_t*)(0xB8000);
    terminal_row = 0;
    terminal_col = 0;
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}


void print(const char* str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}


static struct paging_4gb_chunk* kernel_chunk = 0;

void panic(const char* msg)
{
    print(msg);
    while(1) {}
}

void kernel_page()
{
    kernel_registers();
    paging_switch(kernel_chunk);
}

struct tss tss;

struct gdt gdt_real[PEAROS_TOTAL_GDT_SEGMENTS];
struct gdt_structured gdt_structured[PEAROS_TOTAL_GDT_SEGMENTS] = {
    {.base = 0x00, .limit = 0x00, .type = 0x00},  // NULL segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x9a}, // Kernel code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0x92}, // Kernel data segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf8}, // User code segment
    {.base = 0x00, .limit = 0xffffffff, .type = 0xf2}, // User data segment
    {.base = (uint32_t)&tss, .limit = sizeof(tss), .type = 0xE9} // TSS segment
};

void kernel_main()
{
    terminal_initialize();


    // Initilaize the heap
    kheap_init();

    // Search and initializes the disk
    disk_search_and_init();

    // Initialize the interrupt descriptor table
    idt_init();

    // Setup the TSS
    memset(&tss, 0x00, sizeof(tss));
    tss.esp0 = 0x600000;
    tss.ss0 = KERNEL_DATA_SELECTOR;

    // Load the TSS
    tss_load(0x28);
    // Setup Paging
    kernel_chunk = paging_new_4gb(PAGING_IS_WRITEABLE | PAGING_IS_PRESENT | PAGING_ACCESS_FROM_ALL);

    // Switch to kernel pagin chunk
    paging_switch(kernel_chunk);


    char* ptr = kzalloc(4096);
    paging_set(paging_4gb_chunk_get_directory(kernel_chunk), (void*)0x100, (uint32_t)ptr | PAGING_ACCESS_FROM_ALL | PAGING_IS_PRESENT | PAGING_IS_WRITEABLE);

    // Enable paging
    enable_paging();

    // Registers kernel commands
    isr80h_register_commands();
    // Enable the system interrupts
    //enable_interrupts();

    //pathparser_parse("0:/bin/shell.bin", NULL);

    keyboard_init();

    struct process* process = 0;
    int res = process_load("0:/blank.elf", &process);

    if (res != PEAROS_ALL_OK)
    {
        panic("Failed to load blank.bin\n");
    }

    struct command_argument argument;
    strcpy(argument.argument, "Testing");
    argument.next = 0x00;

    process_inject_arguments(process, &argument);

    res = process_load_switch("0:/blank.elf", &process);
    if(res != PEAROS_ALL_OK)
    {
        panic("Failed to load blank.elf\n");
    }

    strcpy(argument.argument, "ABC\n");
    argument.next = 0x00;

    process_inject_arguments(process, &argument);
    
    task_run_first_ever_task();
}