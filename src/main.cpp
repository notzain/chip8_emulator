#include "chip8.h"

int main(int argc, char **argv) {
    chip8 chip8;

    chip8.load_game_from_file("/home/zain/CLionProjects/chip8/chip8_roms/TETRIS");

    for (int i = 0; i < 4096; ++i) {
        chip8.tick();
    }
}