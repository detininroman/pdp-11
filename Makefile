CXX = g++
TARGET = pdp.bin
CXX_FLAGS = -Wall -pedantic -std=c++11 -c
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o
DEPS = ./gui/Screen.hpp ./gui/GUIObject.hpp ./gui/Button.hpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(SFML_FLAGS) -o $@

%.o: ./%.cpp $(DEPS)
	$(CXX) $(CXX_FLAGS) $<

count:
	find . -name '*.cpp' | xargs wc -l

clean:
	rm $(TARGET) *.o
