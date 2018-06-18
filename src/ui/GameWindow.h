//
// Created by zain on 5/31/18.
//

#ifndef CHIP8_GAMEWINDOW_H
#define CHIP8_GAMEWINDOW_H

#include "ICanvas.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <string>

namespace core {
    class chip8;
}

namespace ui {
    class GameWindow : public sf::RenderWindow {
    private:
        const int _resolution;

        std::unique_ptr<ICanvas> _gameCanvas = nullptr;
        std::unique_ptr<ICanvas> _keypadCanvas = nullptr;

    public:
        GameWindow(core::chip8 &chip8, std::string window_name, int resolution = 10);

        void update();
    };
}


#endif //CHIP8_GAMEWINDOW_H
