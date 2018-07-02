#include <iostream>
#include "debugger.h"

#include "core/chip8.h"
#include "util/logger.h"

namespace dbg {
    debugger::debugger(core::chip8 &chip8) : _chip8(chip8) {}

    bool debugger::enabled() const {
        return _enabled;
    }

    void debugger::enable() {
        util::logger::log(util::logger::type::DEBUG,
                          "--- Debug enabled --- \n");
        _enabled = true;
    }

    void debugger::disable() {
        util::logger::log(util::logger::type::DEBUG,
                          "--- Debug disabled --- \n");
        _enabled = false;
    }

    void debugger::handle() {
        std::cout << "> ";

        std::string message;
        std::getline(std::cin, message);

        std::cout << '\n';

        if (message == "exit") {
            disable();
        }
    }
}
