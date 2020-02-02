# PDP-11 Emulator

### Usage
#### Emulator
1. `make` 
2. `./pdp.bin *name of program to execute*`. 

Ex: `./pdp.bin programs/logo`

Alternatively, for build one can use CMake with `CMakeLists.txt` present.
#### Bytecode generator
1. `cd assembler`
2. `make`
3. `./asm *path to assembler code* *filename*`. 

Ex: `./asm ../programs/white_screen.s white_screen`
#### GUI
Graphical Interface contains:
- The values of the general purpose registers, as well as Processor Status Word flags (N, Z, V, C).
- Number of CPU ticks from the start of the program execution, with and without pipeline optimisation.
- Disassembly and byte code, showing the instructions executed so far.
- The "Step" mode, allowing to execute instructions one by one.
- Two modes for a program execution: the "Start" mode for the slow and the "Execute" mode for the quick execution.
### Overall emulator architecture
- `emulator` class is designed for the pipeline cycle execution (in our case, one cycle consists of *fetch*, *decode*, *load operands*, *execute*). Moreover, it's used for the communication with the GUI, providing the information about memory, registers and the progress of the program execution.
- `instructions` contains the global instruction table and instruction callbacks.
- `memory` contains registers and the continuous space of RAM, video memory and ROM (in this exact order). The sizes of these parts of memory can be modyfied in `emulator/params.hpp`.
- `pipeline` counts the CPU ticks it could spend executing the instructions in two ways: 
    - one by one
    - parallelizing with the pipeline. 

The number of ticks one pipeline stage occupies can be modyfied in `emulator/params.hpp`.

### Authors
- GUI - @detininroman 
- Execution cycle, memory, simple pipeline - @pekashy
- Commands, bytecode generator, example programs - @terana
- Overall architecture - @FflushLife
