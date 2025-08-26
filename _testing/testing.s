;test: take the lib and add functions inside the testing.s file to test the functions functionality

default rel
bits 64

extern ft_itoa
extern ft_strlen
extern strlen

section .bss
    buf_itoa: resb 32

section .data
    str: db 'this is a test', 0
    newline: db 10, 0      ; newline character
    msg_strlen: db 'strlen result: ', 0
    msg_ft_strlen: db 'ft_strlen result: ', 0

section .text
    global _main

_main:
    ; Print the test string
    mov rdi, 1        ; file descriptor (1 = stdout)
    mov rsi, str      ; pointer to the message
    mov rdx, 14       ; length of the message (corrected)
    mov rax, 1        ; syscall number (1 = write)
    syscall           ; call the kernel

    ; Print newline
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    mov rax, 1
    syscall

    ; Print "strlen result: "
    mov rdi, 1
    mov rsi, msg_strlen
    mov rdx, 15
    mov rax, 1
    syscall

    ; Test standard strlen
    mov rdi, str
    call strlen
    mov rdi, rax          ; result goes to rdi for ft_itoa
    mov rsi, buf_itoa
    call ft_itoa

    ; Print newline
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    mov rax, 1
    syscall

    ; Print "ft_strlen result: "
    mov rdi, 1
    mov rsi, msg_ft_strlen
    mov rdx, 17
    mov rax, 1
    syscall

    ; Test our ft_strlen
    mov rdi, str          ; correct: pass string in rdi
    call ft_strlen
    mov rdi, rax          ; result goes to rdi for ft_itoa
    mov rsi, buf_itoa
    call ft_itoa

    ; Print final newline
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    mov rax, 1
    syscall

    ; exit(0)
    mov rdi, 0
    mov rax, 60
    syscall