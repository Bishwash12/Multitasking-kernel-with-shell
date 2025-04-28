#include "process.h"
#include "memory/memory.h"

// The current process that is running
struct process* current_process = 0;

static struct process* processes[PEAROS_MAX_PROCESSES] = {};

static void process_int(struct process* process)
{
    memset(process, 0 , sizeof(struct process));
}

struct process* process_current()
{
    return current_process;
}

int process_load_for_slot(const char* filename, struct  process** process, int process_slot)
{
    
}