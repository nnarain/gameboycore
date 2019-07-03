#pragma once

#include "ui/audio_stream.hpp"
#include "ui/frame_buffer.hpp"
#include "debugger/debugger_interface.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <gameboycore/gameboycore.h>

#include <functional>
#include <map>

class UserInterface
{
public:
    UserInterface(gb::GameboyCore& core, DebuggerInterface& debugger);
    ~UserInterface();

    void run();

private:
    void initialize(gb::GameboyCore& core);
    void update();
    bool isRunning() const;

    void drawUI();
    void drawExecutionControl();
    void drawRegisters();
    void drawDisassembly();
    void drawDisplay();

    void scanlineCallback(const gb::GPU::Scanline& scanline, int line);
    void vblankCallback();

    void handleKeyEvent(sf::Keyboard::Key key, bool pressed);

    sf::RenderWindow window_;
    sf::Clock delta_clock_;

    gb::GameboyCore& core_;
    DebuggerInterface& debugger_;
    gb::CPU::Status state_;

    sf::Sprite screen_sprite_;
    sf::Texture screen_texture_;
    Framebuffer<160, 144, 4> framebuffer_;

    AudioStream audio_stream_;

    std::map<sf::Keyboard::Key, gb::Joy::Key> key_map_;
    std::function<void(gb::Joy::Key, bool)> key_event_;
};