# Nitro Compiler

Nitro is a toy compiler written in C++ that takes a simple `.ni` source file as input, tokenizes it, and generates x86-64 assembly output. It currently supports very minimal functionality: compiling an `exit` statement with a literal exit code into working Linux ELF binaries.

## Features

- Tokenizes custom `.ni` source files  
- Converts tokens into x86-64 assembly instructions  
- Generates an `output.asm` file and compiles it into an ELF executable via **NASM** and **ld** (through WSL on Windows)  
- Example:  
  ```ni
  exit 42;
  ```
  Produces an executable that exits with status code `42`.

## Requirements

- **C++17 or newer** compiler (e.g., `g++` or `clang++`)  
- **NASM** (Netwide Assembler) installed in WSL  
- **ld** (the GNU linker, included with binutils) installed in WSL  

On Windows, this project assumes you are running WSL (Windows Subsystem for Linux).  
On Linux/Mac, you can remove the `wsl` prefixes in the `system` calls in `main.cpp`.

## Build Instructions

1. Clone or download the repository.  
2. Build the compiler:  
   ```bash
   g++ -std=c++17 main.cpp -o nitro
   ```
   Make sure `tokenization.hpp` and its implementation are in the same directory.  

3. Run the compiler on a `.ni` source file:  
   ```bash
   ./nitro test.ni
   ```

4. This generates:  
   - `output.asm` → NASM assembly file  
   - `output.o`   → object file  
   - `output`     → final ELF executable  

## Example

### Input (`test.ni`):
```ni
exit 0;
```

### Usage:
```bash
./nitro test.ni
```

### Output:
Run the generated program:
```bash
./output
echo $?   # prints 0
```

The program exits cleanly with status code `0`.

## Project Structure

```
├── main.cpp            # Compiler entry point
├── tokenization.hpp    # Tokenizer definitions
├── output.asm          # Generated assembly
├── output.o            # Assembled object file
└── output              # Final executable
```

## Notes

- Currently supports only the `exit <literal>;` instruction.  
- Future improvements could include variables, expressions, or more syscalls.  
- Designed as a learning project for compiler construction and low-level programming.  