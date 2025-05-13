#include "keyboard.h"   
#include "kernel.h"
#include "status.h"
#include "task/process.h"

// This is our virtual keyboard layer for abstraction

static struct keyboard* keyboard_list_head = 0;
static struct keyboard* keyboard_list_last = 0;

void keyboard_init()
{

}

int keyboard_insert(struct keyboard* keyboard)
{
    int res = 0;
    if (keyboard->init == 0)
    {
        res = -EINVARG;
        goto out;
    }

    if (keyboard_list_last)
    {
        keyboard_list_last->next = keyboard;
        keyboard_list_last = keyboard;
    }
    else 
    {
        keyboard_list_head = keyboard;
        keyboard_list_last = keyboard;
    }

   
    res = keyboard->init();

out:    
    return res;
}

static int keyboard_get_tail_index(struct process* process)
{
    return process->keyboard.tail % sizeof(process->keyboard.buffer);
}

void keyboard_push(char c)
{
    struct process* process = process_current();
    if (!process)
    {
        return;
    }

    int real_index = keyboard_get_tail_index(process);
    process->keyboard.buffer[real_index] = c;
    process->keyboard.tail++;
}