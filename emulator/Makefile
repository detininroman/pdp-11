CXX = g++
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17
SRC = emulator.cpp memory/memory.cpp instructions/instructions.cpp
TARGET = emulator

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXX_FLAGS) main.cpp $(SRC) -o emulator

obj:
	$(CXX) $(CXX_FLAGS) -c $(SRC)

clean:
	rm $(TARGET) *.o