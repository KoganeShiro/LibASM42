# LibASM42
LibASM42 is a collection of basic C library functions reimplemented in x86-64 assembly (NASM, Intel syntax) for Linux. The goal is to help you understand low-level programming concepts.

## What’s Included

You’ll find assembly implementations for these standard C functions:
- `ft_strlen` — Get the length of a string.
- `ft_strcpy` — Copy one string to another.
- `ft_strcmp` — Compare two strings.
- `ft_strdup` — Duplicate a string (with memory allocation).
- `ft_read` — Read from a file descriptor (system call).
- `ft_write` — Write to a file descriptor (system call).

All functions follow the System V AMD64 ABI calling convention (used on Linux x86-64).

## How to Build

1. **Install NASM**:  
	```sh
	sudo apt-get install nasm
	```
2. **Build the library**:  
	Run `make` in the project directory. This will assemble the `.s` files and create `libasm.a`.

3. **Test the code**:  
	For simpler testing, I created a C file to test my functions. You can use the command as follow :
	```sh
	make test
	```

## Key Concepts for Assembly

Assembly language is a low-level programming language that communicates directly with a computer’s hardware. Here are some essential concepts for getting started:

### Common Instruction Types Use

Below are the main categories of instructions you’ll encounter in the provided assembly code:

- **Data Movement**
      - `mov`: Copy data between registers or between memory and registers.
      - `push` / `pop`: Save or restore register values on the stack.
      - `inc` / `dec`: Increment or decrement a register or memory value.

- **Arithmetic and Logic**
      - `add` / `sub`: Add or subtract values.
      - `xor`: Bitwise exclusive OR (often used to zero a register).
      - `neg`: Negate a value (two’s complement).
      - `test`: Bitwise AND, sets flags but does not store result.
      - `cmp`: Compare two values and set flags for conditional jumps.
      - `movzx`: Move with zero extension (used for unsigned values).

- **Control Flow**
      - `jmp`: Unconditional jump to a label.
      - `je`, `jne`, `jz`, `js`: Conditional jumps based on flags (equal, not equal, zero, sign).
      - `call`: Call a function or procedure.
      - `ret`: Return from a function.

- **System and External Calls**
      - `syscall`: Make a system call to the operating system.
      - `extern`: Declare external functions used (e.g., `malloc`, `__errno_location`).

Each instruction type serves a specific purpose, from moving data and performing calculations to controlling program flow and interacting with the OS.

### x86-64 Registers Visualization

```
┌─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┬─────────────┐
│   rax       │   rbx       │   rcx       │   rdx       │   rsi       │   rdi       │   rsp       │   rbp       │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│ Accumulator │ Base        │ Counter     │ Data        │ Source      │ Dest        │ Stack Ptr   │ Base Ptr    │
├─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┼─────────────┤
│  rax (64b)  │  rbx (64b)  │  rcx (64b)  │  rdx (64b)  │  rsi (64b)  │  rdi (64b)  │  rsp (64b)  │  rbp (64b)  │
│  eax (32b)  │  ebx (32b)  │  ecx (32b)  │  edx (32b)  │  esi (32b)  │  edi (32b)  │  esp (32b)  │  ebp (32b)  │
│   ax (16b)  │   bx (16b)  │   cx (16b)  │   dx (16b)  │   si (16b)  │   di (16b)  │   sp (16b)  │   bp (16b)  │
│   al (8b)   │   bl (8b)   │   cl (8b)   │   dl (8b)   │  sil (8b)   │  dil (8b)   │  spl (8b)   │  bpl (8b)   │
└─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┴─────────────┘

All general-purpose registers in x86-64 are 64 bits wide (8 bytes), but you can access their lower 32, 16, and 8 bits as shown above.

Registers are used for arithmetic, data movement, and function arguments.
Example usage:
      rax: used for return values, arithmetic
      rdi/rsi/rdx/rcx/r8/r9: used for function arguments
      rsp: points to the top of the stack
      rbp: used as a frame/base pointer in functions
```

- **Calling Convention**: A calling convention is a set of rules that defines how functions receive parameters from the caller and how they return results. It specifies which registers or stack locations are used for arguments and return values, how the stack is managed, and which registers must be preserved across function calls. This ensures that separately written functions can work together reliably, regardless of the language or compiler used.

- **Function Calling Convention**: On Linux x86-64, the first six function arguments are passed in registers (`rdi`, `rsi`, `rdx`, `rcx`, `r8`, `r9`). Return values are placed in `rax`. Additional arguments go on the stack.

- **Stack and Stack Alignment**: The stack is a region of memory used for function calls and local variables. The stack pointer (`rsp`) must be 16-byte aligned before calling a function.
Here’s a simple example of stack manipulation:

```
rsp → ┌─────────────┐
      │ return addr │  ← Return address to caller
      ├─────────────┤
      │             │

After push rbx:
      ┌─────────────┐
      │ original    │  ← Original rbx value
      │ rbx value   │
rsp → ├─────────────┤
      │ return addr │
      ├─────────────┤
      │             │

After pop rbx:
rsp → ┌─────────────┐
      │ return addr │  ← Back to original state
      ├─────────────┤  (and rbx restored)
      │             │
```

## Resources for Learning Assembly

__FR__
- [Openclassrom](https://openclassrooms.com/fr/courses/2288321-apprenez-a-programmer-en-assembleur-x86/2288775-introduction-installation)
- [langage_asm_Intel_64bits](http://lacl.u-pec.fr/tan/asm.pdf)
- [cours_nasm](https://www.unilim.fr/pages_perso/tristan.vaccon/cours_nasm.pdf)
---
__EN__
- [Tutorialspoint](https://www.tutorialspoint.com/assembly_programming/assembly_introduction.htm)
- [nasmtutorial](https://cs.lmu.edu/~ray/notes/nasmtutorial/)
- [asmx64](https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf)

[syscall table](https://filippo.io/linux-syscall-table/)
[registers](https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html)