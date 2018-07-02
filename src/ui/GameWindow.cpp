//
// Created by zain on 5/31/18.
//
#include "GameWindow.h"

#include "ui/canvas/GameCanvas.h"
#include "ui/canvas/KeypadCanvas.h"

#include "core/chip8.h"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ui {
    template <typename Func>
    void render (sf::RenderWindow& window, Func &&f) {
        window.clear();
        f();
        window.display();
    };

    GameWindow::GameWindow(core::chip8 &chip8, std::string window_name, int resolution)
            : _resolution(resolution),
              sf::RenderWindow(sf::VideoMode(64, 32), window_name) {

        _gameCanvas = std::make_unique<GameCanvas>(chip8, 0, 0, _resolution);
        _keypadCanvas = std::make_unique<KeypadCanvas>(chip8, _gameCanvas->size_x(), 0, _resolution);

        sf::Vector2u const size(_gameCanvas->size_x() * _resolution + _keypadCanvas->size_x() * _resolution,
                                _gameCanvas->size_y() * _resolution);

        create({size.x, size.y}, window_name);
    }

    void GameWindow::update() {
        sf::Event event{};
        while (pollEvent(event)) {
            switch(event.type){
                case sf::Event::Closed: { close(); break; }
            }
        }
        render(*this, [&] {
            _gameCanvas->render(*this);
            _keypadCanvas->render(*this);
        });

    }
}
