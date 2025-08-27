default rel
bits 64

section .text
        global ft_strlen

; ft_strlen(rdi = arg string pointer)
; Returns length in rax
ft_strlen:
    mov rax, 0             ; counter = 0
    .loop:
        cmp byte [rdi], 0
        je .end_loop
        inc rax            ; increment counter
        inc rdi            ; move to next character
        jmp .loop
    .end_loop:
        ret                ; return counter in rax
