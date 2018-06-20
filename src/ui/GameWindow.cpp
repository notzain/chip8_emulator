//
// Created by zain on 5/31/18.
//
#include "GameWindow.h"

#include "GameCanvas.h"
#include "KeypadCanvas.h"

#include "core/chip8.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ui {
    GameWindow::GameWindow(core::chip8 &chip8, std::string window_name, int resolution)
            : _resolution(resolution),
              sf::RenderWindow(sf::VideoMode(5, 5), window_name) {

        _gameCanvas = std::make_unique<GameCanvas>(chip8, 0, 0, _resolution);
        _keypadCanvas = std::make_unique<KeypadCanvas>(chip8, 64, 0, _resolution);

        sf::Vector2u const size(_gameCanvas->size_x() * _resolution + _keypadCanvas->size_x() * _resolution,
                                _gameCanvas->size_y() * _resolution);

        create({size.x, size.y}, window_name);
    }

    void GameWindow::update() {
        sf::Event event{};
        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                close();
        }

        this->clear();

        _gameCanvas->render(*this);
        _keypadCanvas->render(*this);

        this->display();
    }
}
