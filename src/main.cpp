#include "core/chip8.h"
#include "ui/GameWindow.h"

#include <iostream>
#include <string>
#include <sstream>
#include <thread>

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return std::move(tokens);
}

int main(int argc, char **argv) {
    std::string const game_file = [&]() -> std::string {
        if (argc > 1) {
            return argv[1];
        }
        return "/home/zain/CLionProjects/chip8_emulator/chip8_roms/TETRIS";
    }();

    core::chip8 chip8;

    ui::GameWindow game_window(chip8, "Chip8 - " + split(game_file, '/').back(), 10);

    chip8.load_game_from_file(game_file.c_str());

    while (game_window.isOpen()) {
        chip8.tick();

        game_window.update();
    }
}
