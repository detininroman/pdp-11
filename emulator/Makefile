CXX = g++
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -Werror
SRC = emulator.cpp memory/memory.cpp instructions/instructions.cpp pipeline.cpp
INC = emulator.hpp memory/memory.hpp instructions/instructions.hpp pipeline.hpp
TARGET = emulator

all: $(TARGET)

$(TARGET): $(SRC) $(INC) main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp $(SRC) -o emulator

obj: $(SRC) $(INC)
	$(CXX) $(CXX_FLAGS) -c $(SRC)

clean:
	rm $(TARGET) *.o