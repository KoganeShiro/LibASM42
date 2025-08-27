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

    ; call ft_strlen
    call ft_strlen ; will take rdi as param and return rax
    ; allocate the memory using malloc
    add rax, 1
    mov rcx, rdi ;src
    mov rdi, rax
    call _malloc ;rdi is the param
    cmp rax, 0
    je .malloc_fail
    ; strcpy src_str dest_str
    call strcpy
    ret

    .malloc_fail:
        mov rax, 0
        ret

