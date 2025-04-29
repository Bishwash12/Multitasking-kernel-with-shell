[BITS 32]

section .asm

global restore_general_purpose_registers

task_return:
    mov ebp, esp
    ; Push the data segment ((ss will be fine))
    ; Push the stack address
    ; Push the flags
    ; Push the code segment
    ; Push IP

    ; Let's access the structure passed to us
    mov ebx, [ebp+4]
    push dword

restore_general_purpose_registers:
    push ebp
    mov ebp, esp
    mov ebx, [ebp+8]
    mov edi, [ebx]
    mov esi, [ebx+4]
    mov ebp, [ebx+8]
    mov edx, [ebx+16]
    mov ecx, [ebx+20]
    mov eax, [ebx+24]
    mov ebx, [ebx+12]
    pop ebp
    ret