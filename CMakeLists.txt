cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

set(CHIP8 src/chip8.cpp src/chip8.h src/gfx.cpp src/gfx.h src/cpu.cpp src/cpu.h src/ram.cpp src/ram.h)

set(SRC main.cpp)

add_executable(chip8 ${SRC} ${CHIP8})
