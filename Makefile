CXX = g++
TARGET = pdp
CXX_FLAGS = -Wall -pedantic -std=c++11 -c
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o Screen.o GUIObject.o Button.o
DEPS = ./src/Screen.h ./src/GUIObject.h ./src/Button.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $^ $(SFML_FLAGS) -o $@

%.o: ./src/%.cpp $(DEPS)
	$(CXX) $(CXX_FLAGS) $<

count:
	find . -name '*.cpp' | xargs wc -l

clean:
	rm $(TARGET) *.o
