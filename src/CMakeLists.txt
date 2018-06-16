#include_directories(util)
include_directories(core)
include_directories(ui)

#add_subdirectory(util)
add_subdirectory(core)
add_subdirectory(ui)

add_executable(chip8 main.cpp)

target_link_libraries(chip8 core ui)
