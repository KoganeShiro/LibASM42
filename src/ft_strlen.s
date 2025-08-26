default rel
bits 64

section .text
        global ft_strlen

; ft_strlen(rdi = string pointer)
; Returns length in rax
ft_strlen:
    xor rax, rax           ; counter = 0
    .loop:
        cmp byte [rdi], 0  ; compare current char with null
        je .end_loop       ; if null, exit loop
        inc rax            ; increment counter
        inc rdi            ; move to next character
        jmp .loop
    .end_loop:
        ret                ; return counter in rax
