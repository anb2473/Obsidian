; nasm cmd: nasm -f win64 out.asm -o out.obj
; run w/ -f win64 to specify compilation to Windows on a 64 bit OS

; linker cmd: ld out.obj -o out.exe -lkernel32
; Link kernal for I/O operations
section .bss
    written resd 1           ; DWORD for WriteConsoleA

section .rodata
    msg db 'Hello, World!', 0x0A, 0

section .text
global _start
extern GetStdHandle
extern WriteConsoleA
extern ExitProcess

get_handle:
    sub rsp, 32
    mov ecx, -11
    sub rsp, 8
    call GetStdHandle
    add rsp, 8
    add rsp, 32
    ret

print:
    sub rsp, 32           ; shadow space
    sub rsp, 8
    call WriteConsoleA
    add rsp, 8
    add rsp, 32
    ret

str_len:
    xor rax, rax
.loop:
    mov bl, byte [rcx + rax]
    cmp bl, 0
    je .done
    inc rax
    jmp .loop
.done:
    ret

main:
    sub rsp, 32           ; just shadow space for calls

    lea rcx, [rel msg]

    add rsp, 8
    call str_len
    sub rsp, 8

    mov r8, rax           ; length

    add rsp, 8
    call get_handle
    sub rsp, 8

    mov rcx, rax          ; handle

    lea rdx, [rel msg]    ; string pointer
    lea r9, [rel written] ; pointer to DWORD in .bss

    add rsp, 8
    call print
    sub rsp, 8

    xor rax, rax          ; set return value to 0
    add rsp, 32

    ret

_start:                     ; _start will be generated before main is run
    sub rsp, 32

    sub rsp, 8              ; Ever time 'call' is written 8 bytes are taken for the return address (where to resume execution),
                            ; so we take 8 bytes to balance the stack
    call main
    add rsp, 8
    mov rcx, rax

    add rsp, 32

    call ExitProcess
