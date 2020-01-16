CXX = g++
CXX_FLAGS = -Wall -pedantic -O2 -std=c++17 -Werror
SRC = bit_array.cpp
INC = bit_array.hpp

misc_obj: $(SRC) $(INC)
	$(CXX) $(CXX_FLAGS) -c $(SRC) -o misc.o

clean:
	rm *.o