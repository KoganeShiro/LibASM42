default rel         ; ensure RIP-relative addressing (safe default)
bits 64             ; assemble for 64-bit mode

; (Read-Only Data) --> constant strings
section .rodata
    msg:    db 'Hello world', 10
    ; msg is a label pointing to a string in memory
    ;db means define byte, so the bytes of the string are stored here.
    ;(10 is ASCII for newline).

    msglen: equ $-msg
    ;msglen: equ $-msg defines the length of the string.
    ;$ means "the current address", so $ - msg is the difference between the end of the string and its start.

section .text
        global hello_world
; The .text section holds the actual instructions (the "code" part).
; global hello_world tells the linker that the entry point of the program is hello_world

    hello_world:
        ; write(1, msg, msglen)
        mov rdi, 1        ; file descriptor (1 = stdout)
        mov rsi, msg      ; pointer to the message
        mov rdx, msglen   ; length of the message
        mov rax, 1        ; syscall number (1 = write)
        syscall           ; call the kernel

        ; exit(0)
        ; mov rdi, 0        ; exit status code
        ; mov rax, 60       ; syscall number (60 = exit)
        ; syscall
