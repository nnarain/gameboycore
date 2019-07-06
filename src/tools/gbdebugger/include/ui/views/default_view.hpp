#pragma once

#include "ui/views/view.hpp"
#include "ui/frame_buffer.hpp"
#include "debugger/debugger_interface.hpp"

#include <SFML/Graphics.hpp>

#include <gameboycore/gameboycore.h>

//! Default debugger display
class DefaultView : public View
{
public:
    DefaultView(gb::GameboyCore& core, DebuggerInterface& debugger);
    ~DefaultView() = default;

private:
    virtual std::string name() override;
    virtual void render() override;

    void drawExecutionControl();
    void drawRegisters();
    void drawDisassembly();
    void drawDisplay();

    void scanlineCallback(const gb::GPU::Scanline& scanline, int line);
    void vblankCallback();

    gb::GameboyCore& core_;
    DebuggerInterface& debugger_;
    gb::CPU::Status state_;

    sf::Sprite screen_sprite_;
    sf::Texture screen_texture_;
    Framebuffer<160, 144, 4> framebuffer_;
};
