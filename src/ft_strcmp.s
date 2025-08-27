default rel
bits 64

section .text
    global ft_strcmp

; Arguments: rdi = s1, rsi = s2
; Returns: <0 if s1<s2, 0 if s1==s2, >0 if s1>s2
ft_strcmp:
    .loop:
        mov al, [rdi]
        mov bl, [rsi]
        cmp al, bl
        jne .not_equal
        test al, al         ; al & al and update flags (like the zero flag)
        jz .equal           ; jump if zero flag true
        inc rdi
        inc rsi
        jmp .loop
        
    .not_equal:
        movzx rax, al       ; Zero-extend al to rax (like calloc)
        movzx rbx, bl       ; Zero-extend bl to rbx  
        sub rax, rbx        ; rax = al - bl
        ret
        
    .equal:
        xor rax, rax        ; Return 0 (strings are equal)
        ret