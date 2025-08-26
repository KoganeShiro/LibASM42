default rel
bits 64

section .text
    global ft_itoa

; ======================================================
; ft_itoa(rdi = integer, rsi = buffer)
; - Converts integer to string in buffer
; - Prints it to stdout using write syscall
; ======================================================
ft_itoa:
    push rsi               ; save original buffer pointer
    mov rax, rdi
    mov rbx, 10

    cmp rax, 0
    jne .convert
    mov byte [rsi], '0'
    inc rsi
    mov byte [rsi], 0
    jmp .print

.convert:
    mov r8, rsi
    add r8, 19             ; point to end of buffer space
    mov r9, r8

.loop:
    xor rdx, rdx
    div rbx
    add dl, '0'
    mov [r9], dl
    dec r9
    test rax, rax
    jnz .loop

    inc r9

.copy:
    mov al, [r9]
    mov [rsi], al
    inc rsi
    inc r9
    cmp r9, r8
    jbe .copy

    mov byte [rsi], 0

; ------------------------------------------------------
; .print: compute string length & call write
; ------------------------------------------------------
.print:
    pop rsi                ; restore original buffer pointer
    push rsi               ; save it again for potential reuse
    xor rcx, rcx
.len_loop:
    cmp byte [rsi+rcx], 0
    je .len_done
    inc rcx
    jmp .len_loop
.len_done:
    mov rdx, rcx           ; length of string

    mov rdi, 1             ; fd = stdout
    mov rax, 1             ; syscall: write
    syscall

    pop rsi                ; restore buffer pointer
    ret