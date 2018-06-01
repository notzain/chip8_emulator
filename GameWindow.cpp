//
// Created by zain on 5/31/18.
//
#include "GameWindow.h"
#include "src/chip8.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

GameWindow::GameWindow(chip8 &chip, std::string window_name, int resolution)
        : _chip8(chip),
          _resolution(resolution),
          sf::RenderWindow(sf::VideoMode(64 * resolution, 32 * resolution), window_name) {}

void GameWindow::update() {
    sf::Event event{};
    while (pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            close();
    }

    if (_chip8.to_draw()) {
        clear();

        sf::RectangleShape pixel({_resolution, _resolution});
        for (int x = 0; x < 64; x++) {
            for (int y = 0; y < 32; ++y) {
                if (_chip8.pixel_at(x, y)) {
                    pixel.setPosition(x * _resolution, y * _resolution);
                    draw(pixel);
                }
            }
        }

        display();
        _chip8.has_drawn();
    }
}
