default rel
bits 64

section .text
        global ft_strcpy


ft_strcpy:  
    ;have two parameter: src and dest
    ;we should copy char by char from the src to the dest
    ;incrementing for each until null
    mov rcx, 0
    .loop:
        mov al, [rdi + rcx] ; Load byte from src
        mov [rsi + rcx], al  ; Store byte to dest
        inc rcx
        cmp al, 0
        je .loop
        ret
