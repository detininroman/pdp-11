CXX = g++
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -Werror
SRC = assembler.cpp
INC = assembler.hpp instructions.hpp
TARGET = asm

all: $(TARGET)

$(TARGET): $(SRC) $(INC) main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp $(SRC) -o asm

obj: $(SRC) $(INC)
	$(CXX) $(CXX_FLAGS) -c $(SRC)

clean:
	rm $(TARGET) *.o