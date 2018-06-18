//
// Created by zain on 5/31/18.
//
#include "GameWindow.h"

#include "core/chip8.h"

#include "GameCanvas.h"
#include "KeypadCanvas.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ui {
    GameWindow::GameWindow(core::chip8 &chip8, std::string window_name, int resolution)
            :
            _resolution(resolution),
            sf::RenderWindow(sf::VideoMode(5,5), window_name) {

        _gameCanvas = std::make_unique<GameCanvas>(chip8, 0, 0);
        _keypadCanvas = std::make_unique<KeypadCanvas>(chip8, 64, 0);

        sf::Vector2u const size(_gameCanvas->size_x() * resolution + _keypadCanvas->size_x() * resolution,
                                _gameCanvas->size_y() * resolution);

        create({size.x, size.y}, window_name);
    }

    void GameWindow::update() {
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                close();
        }

        _gameCanvas->render(*this, _resolution);
        _keypadCanvas->render(*this, _resolution);
    }
}
