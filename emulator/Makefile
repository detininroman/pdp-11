CXX = g++
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -Werror
SRC = emulator.cpp memory/memory.cpp instructions/instructions.cpp
TARGET = emulator

all: $(TARGET)

$(TARGET): $(SRC) main.cpp
	$(CXX) $(CXX_FLAGS) main.cpp $(SRC) -o emulator

obj: $(SRC)
	$(CXX) $(CXX_FLAGS) -c $(SRC)

clean:
	rm $(TARGET) *.o