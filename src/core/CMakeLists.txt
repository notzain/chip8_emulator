set(CORE_FILES
        chip8.h
        chip8.cpp
        cpu.h
        cpu.cpp
        ram.h
        ram.cpp
        gfx.h
        gfx.cpp
        keypad.h
        keypad.cpp)

add_library(core ${CORE_FILES})
target_link_libraries(core fmt-header-only)

