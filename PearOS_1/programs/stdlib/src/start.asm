[BITS 32]

global _start
extern c_start
extern pearos_exit

section .asm

_start:
    call c_start
    call pearos_exit
    ret

