default rel
bits 64

section .text
        global ft_strcpy


ft_strcpy:  
    ;have two parameter: rdi = dest, rsi = src  
    ;we should copy char by char from the src to the dest
    ;incrementing the index until null
    ;ret: pointer to dest (rdi)
    mov rcx, 0
    .loop:
        mov al, [rsi + rcx] ; Load single byte from src
        mov [rdi + rcx], al  ; Store byte to dest
        inc rcx
        cmp al, 0
        jne .loop
        mov rax, rdi
        ret
