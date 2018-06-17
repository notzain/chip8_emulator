cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED graphics window system)
include_directories(${SFML_INCLUDE_DIR})

include_directories(lib/fmt-5.0.0/include)
add_subdirectory(lib/fmt-5.0.0)

add_subdirectory(src)
