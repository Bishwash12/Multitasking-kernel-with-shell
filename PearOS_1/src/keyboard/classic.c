#include "keyboard.h"

int classic_keyboard_init();

struct keyboard classic_keyboard = {
    .name = {"Classic"},
    .init = classic_keyboard_init
};

int classic_keyboard_init()
{
    return 0;
}

struct keyboard* classic_init()
{
    return &classic_keyboard;
}