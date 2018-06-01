#include "src/chip8.h"
#include "GameWindow.h"
#include "KeypadWindow.h"

#include <iostream>
#include <string>
#include <sstream>

std::vector<std::string> split (const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return std::move(tokens);
}

int main(int argc, char **argv) {
    std::string const game_file = [&]() -> std::string {
        if (argc > 1) {
            return argv[1];
        }
        return "/home/zain/CLionProjects/chip8/chip8_roms/TETRIS";
    }();

    chip8 chip8;

    GameWindow game_window(chip8, "Chip8 - " + split(game_file, '/').back(), 10);
    game_window.setFramerateLimit(20);

    KeypadWindow keypad_window(chip8, "Chip8 - Keypad", 10);

    chip8.load_game_from_file(game_file.c_str());

    while (game_window.isOpen() && keypad_window.isOpen()) {
        chip8.tick();

        game_window.update();
        keypad_window.update();
    }
}
