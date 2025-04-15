#ifndef DISK_H
#define DISK_H

#include "fs/file.h"

typedef unsigned int PEAROS_DISK_TYPE;

// Represents a real physical hard disk
#define PEAROS_DISK_TYPE_REAL 0
struct disk
{
    PEAROS_DISK_TYPE type;
    int sector_size; 
    // The id of the disk
    int id;
    struct filesystem* filesystem;

    // Private data of our filesystem
    void* fs_private;
};

void disk_search_and_init();
struct disk* disk_get(int index);
int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf);
#endif