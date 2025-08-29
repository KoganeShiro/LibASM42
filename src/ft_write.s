default rel
bits 64

extern __errno_location

section .text
    global ft_write

; Arguments:
    ;rdi      ; file descriptor
    ;rsi      ; buffer
    ;rdx      ; length of the buffer
; Returns: len of the char written and -1 if error (set erno)
ft_write:
    mov rax, 1        ; syscall number (1 = write)
    syscall
    test rax, rax
    js .error         ;sign flag, set if negative
    ret

    .error:
        mov rcx, rax
        neg rcx
        call __errno_location wrt ..plt ;get pointer of errno in rax
        mov [rax], rcx
        mov rax, -1
        ret

