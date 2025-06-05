#include "pearos.h"
#include "stdlib.h"
#include "stdio.h"

int main(int argc, char** argv)
{
    print("Hello how are you!\n");

    print(itoa(876));
    void* ptr = malloc(512);
    free(ptr);
    if (ptr)
    {
        
    }
    while(1) {
        if (getkey() != 0)
        {
            print("Key was pressed\n");
        }
    }
    return 0;
}