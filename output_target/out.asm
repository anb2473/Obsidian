; nasm cmd: nasm -f win64 out.asm -o out.obj
; run w/ -f win64 to specify compilation to Windows on a 64 bit OS

; linker cmd: ld out.obj -o out.exe -lkernel32
; Link kernal for I/O operations

extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

; There is also .data, for non consts, and .bss for unitialized
section .rodata                     ; read only data (consts)
    msg db 'Hello, World!', 0x0A    ; dynamically allocate memory for char*
                                    ; 0x0A is \n
    msg_len equ $ - msg             ; equ defines constant
                                    ; $ is the start of the current line (so $ - msg is the end of the str - the beginning)
    STD_OUTPUT_HANDLE dq -11        ; constant for stdout

section .text
global main, print
get_handle:
    sub rsp, 40            ; reserve shadow space
    mov ecx, -11           ; STD_OUTPUT_HANDLE
    call GetStdHandle       ; handle returned in rax
    add rsp, 40            ; restore stack
    ret

print:
    sub rsp, 40                ; reserve 32-byte shadow space

    lea r9, [rsp+32]           ; pointer for DWORD chars written (4th argument)
    call WriteConsoleA

    add rsp, 40                ; restore shadow space
    ret

str_len:
    xor rax, rax        ; rax = 0, will store length

    .loop:
        mov bl, byte [rcx + rax] ; load byte at string[offset]
        cmp bl, 0                ; check for null terminator
        je .done                 ; if zero, end of string
        inc rax                  ; increment length
        jmp .loop

    .done:
        ret

main:
    ; rdx = pointer to msg, rcx = length
    ; r8  = reserved (NULL)
    ; r9  = pointer to number of chars written

    sub rsp, 40              ; reserve 32 bytes for shadow space
    lea rcx, [rel msg]       ; pointer to string, rel tells it its a pointer
    call str_len             ; output to rax
    mov r8, rax              ; length
    call get_handle          ; output to rax
    mov ecx, rax             ; get console handle
    call print               ; call new function
    xor ecx, ecx             ; ecx always == ecx, so this stores 0 in ecx
                             ; use over mov ecx, 0, as it uses less memory in bytecode
                             ; ecx is return code
    call ExitProcess         ; exit