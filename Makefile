CXX = g++
TARGET = pdp.bin
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -Werror -c
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -pthread
OBJECTS = main.o emulator/emulator.o emulator/instructions.o emulator/memory.o
DEPS = ./gui/Screen.hpp ./gui/GUIObject.hpp ./gui/Button.hpp

all: emul $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(SFML_FLAGS) -o $@

%.o: ./%.cpp $(DEPS)
	$(CXX) $(CXX_FLAGS) $<

emul:
	cd emulator && make obj

count:
	find . -name '*.cpp' | xargs wc -l

clean:
	rm $(TARGET) *.o && cd emulator && make clean
