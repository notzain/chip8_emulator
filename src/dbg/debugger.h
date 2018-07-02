#ifndef CHIP8_DEBUGGER_H
#define CHIP8_DEBUGGER_H

namespace core {
    class chip8;
}

namespace dbg {
    class debugger {
    private:
        core::chip8 &_chip8;

        bool _enabled = false;

    public:
        debugger(core::chip8 &chip8);
        virtual ~debugger() = default;

        bool enabled() const;

        void enable();
        void disable();

        void handle();

    };
}

#endif //CHIP8_DEBUGGER_H
