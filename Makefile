CXX = g++
TARGET = pdp.bin
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -c
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o emulator/emulator.o emulator/instructions.o emulator/memory.o misc/misc.o
DEPS = ./gui/Screen.hpp ./gui/GUIObject.hpp ./gui/Button.hpp

all: emul misc_t $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(SFML_FLAGS) -o $@

%.o: ./%.cpp $(DEPS)
	$(CXX) $(CXX_FLAGS) $<

emul:
	cd emulator && make obj

misc_t:
	cd misc && make misc_obj

count:
	find . -name '*.cpp' | xargs wc -l

clean:
	rm $(TARGET) *.o && cd emulator && make clean
