# PDP-11 Emulator

### Usage
#### Emulator
1. `make` 
2. `./pdp.bin *name of program to execute*`. Ex: `./pdp.bin programs/logo` 
#### Bytecode generator
1. `cd assembler`
2. `make`
3. `./asm *path to assembler code* *filename*`. 
Ex: `./asm ../programs/white_screen.s white_screen`


### Authors
- GUI - @detininroman 
- Execution cycle, memory, simple pipeline - @pekashy
- Commands, bytecode generator, example programs - @terana
- Overall Architecture - @FflushLife
