#include "src/chip8.h"
#include "src/gfx.h"

#include <iostream>
#include <string>

int main(int argc, char **argv) {
    std::string const game_file = [&]() -> std::string {
        if (argc > 1) {
            return argv[1];
        }
        return "/home/zain/CLionProjects/chip8/chip8_roms/TETRIS";
    }();

    chip8 chip8;

    chip8.load_game_from_file(game_file.c_str());

    for (int i = 0; i < 4096; ++i) {
        chip8.tick();
    }
}
