[BITS 32]

global print:function
global getkey:function
global pearos_malloc:function

print:
    push ebp
    mov ebp, esp
    push dword[ebp+8]
    mov eax, 1 ; Command print
    int 0x80

    add esp, 4
    pop ebp
    ret

; int getkey()
getkey:
    push ebp
    mov ebp, esp
    mov eax, 2 ; Command getkey
    int 0x80
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
