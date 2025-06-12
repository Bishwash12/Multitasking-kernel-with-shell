[BITS 32]

global _start
extern c_start

section .asm

_start:
    call C_start
    ret

