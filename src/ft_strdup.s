default rel
bits 64

extern ft_strlen
extern ft_strcpy
extern _malloc

section .text
    global ft_strdup

; Arguments: rdi, src_str
; Returns: ptr to the new duplicate str (dest_str)
ft_strdup:
    ; take the src_str allocating the memory to duplicate it to dest_str
    push rbx
    mov rbx, rdi
    
    call ft_strlen 
    add rax, 1 
    mov rdi, rax    ; Size parameter for malloc
    call _malloc 
    
    cmp rax, 0      ; Check if malloc failed
    je .malloc_fail
    
    ; Set up parameters for ft_strcpy(dest, src)
    mov rdi, rax    ; dest
    mov rsi, rbx    ; src
    call ft_strcpy
    
    ; rax already contains the allocated memory address
    pop rbx
    ret
    
.malloc_fail:
    mov rax, 0
    pop rbx 
    ret

