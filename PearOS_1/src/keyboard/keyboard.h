#ifndef KEYBOARD_H
#define KEYBOARD_H

typedef int (*KEYBOARD_INIT_FUNCTION)();

struct keyboard
{
    KEYBOARD_INIT_FUNCTION init;
    char name[20];
    struct keyboard* next;

};

void keyboard_init();


#endif