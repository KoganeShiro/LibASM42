# LibASM42

On 64-bit systems using NASM with Intel syntax, the calling convention for functions follows the System V AMD64 ABI on Linux (also called the "Unix x86-64 calling convention"). This convention specifies exactly which registers should be used to pass arguments, return values, and handle function calls

Function Arguments:
1st: rdi
2nd: rsi
3rd: rdx
4th: rcx
5th: r8
6th: r9
Additional arguments are passed on the stack.

Return Value:
Use `rax` for integer and pointer return values.

**About `eax` and `rax`:**
- `rax` is the full 64-bit register.
- `eax` is the lower 32 bits of `rax`.
- `ax` is the lower 16 bits of `rax`.
- `al` is the lowest 8 bits of `rax`.

**Usage:**
- For 64-bit return values, use `rax`.
- For 32-bit return values, use `eax`.
- For 16-bit return values, use `ax`.
- For 8-bit return values, use `al`.

Caller-Saved Registers (must be preserved by the caller):
rax, rcx, rdx, rsi, rdi, r8, r9, r10, r11

Callee-Saved Registers (must be preserved by the callee):
rbx, rsp, rbp, r12, r13, r14, r15

Stack Alignment:
The stack pointer (rsp) must be 16-byte aligned before calling a function.

Null-Terminated Strings:
Strings are passed as pointers (usually in rdi for the first argument).

For Linux NASMFLAGS: -f elf

https://filippo.io/linux-syscall-table/

https://community.lambdatest.com/t/understanding-the-test-instruction-in-assembly-language/31686/2

__FR__
- [Openclassrom](https://openclassrooms.com/fr/courses/2288321-apprenez-a-programmer-en-assembleur-x86/2288775-introduction-installation)
- [langage_asm_Intel_64bits](http://lacl.u-pec.fr/tan/asm.pdf)
- [cours_nasm](https://www.unilim.fr/pages_perso/tristan.vaccon/cours_nasm.pdf)
---
__EN__
- [Tutorialspoint](https://www.tutorialspoint.com/assembly_programming/assembly_introduction.htm)
- [nasmtutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
- [asmx64](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)