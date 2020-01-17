cmake_minimum_required(VERSION 3.15)
project(PDP_11)

set(CMAKE_CXX_STANDARD 17)

add_executable(pdp-11 emulator/memory/memory.cpp main.cpp emulator/memory/memory.hpp emulator/params.hpp emulator/emulator.cpp emulator/emulator.hpp emulator/instructions/instructions.cpp emulator/pipeline.hpp emulator/pipeline.cpp)