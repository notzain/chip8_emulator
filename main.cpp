#include "src/chip8.h"
#include "src/gfx.h"

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

int main(int argc, char **argv) {

    constexpr int resolution = 10;

    sf::RenderWindow window(sf::VideoMode(64 * resolution, 32 * resolution), "SFML works!");
    window.setFramerateLimit(60);

    std::string const game_file = [&]() -> std::string {
        if (argc > 1) {
            return argv[1];
        }
        return "/home/zain/CLionProjects/chip8/chip8_roms/TETRIS";
    }();

    chip8 chip8;

    chip8.load_game_from_file(game_file.c_str());

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        chip8.tick();

        if (chip8.to_draw()) {
            window.clear();

            sf::RectangleShape pixel({resolution, resolution});
            for (int x = 0; x < 64; x++) {
                for (int y = 0; y < 32; ++y) {
                    if (chip8.pixel_at(x, y)) {
                        pixel.setPosition(x * resolution, y * resolution);
                        window.draw(pixel);
                    }
                }
            }
            window.display();
            chip8.has_drawn();
        }

    }
}
