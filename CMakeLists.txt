cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

set(CHIP8 src/chip8.cpp src/chip8.h src/gfx.cpp src/gfx.h src/cpu.cpp src/cpu.h src/ram.cpp src/ram.h src/keypad.cpp src/keypad.h)
set(SRC main.cpp)

add_executable(chip8 ${SRC} ${CHIP8})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(chip8 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


