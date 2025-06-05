[BITS 32]

section .asm

global print:function
global pearos_getkey:function
global pearos_malloc:function
global pearos_free:function
global pearos_putchar:function

print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1 ; Command print
    int 0x80

    add esp, 4
    pop ebp
    ret

; int pearos_getkey()
pearos_getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; Command getkey
    int 0x80
    pop ebp
    ret

; void pearos_putchar(char c)
pearos_putchar:
    push ebp
    mov ebp, esp
    mov eax, 3 ; Command putchar
    push dword [ebp+8] ; Variable "c"
    int 0x80
    add esp, 4
    pop ebp
    ret

; void* pearos_malloc(size_t size)
pearos_malloc:
    push ebp
    mov ebp, esp
    mov eax, 4 ; command malloc
    push dword[ebp+8] ; Variable "size"

    int 0x80
    add esp, 4
    pop ebp
    ret

; void pearos_free(void* ptr)
pearos_free:
    push ebp
    mov ebp, esp
    mov eax, 5 ; Command 5 free ( Frees the allocated memory for this process)
    push dword[ebp+8]
    int 0x80
    add esp, 4
    pop ebp
    ret