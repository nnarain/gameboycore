#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "frame_buffer.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <gameboycore/gameboycore.h>

class UserInterface
{
public:
    UserInterface();
    ~UserInterface();

    void initialize(gb::GameboyCore& core);

    void update();

    bool isRunning() const;

    void scanlineCallback(const gb::GPU::Scanline& scanline, int line);
    void vblankCallback();

private:
    sf::RenderWindow window_;
    sf::Clock delta_clock_;

    sf::RectangleShape screen_rect_;
    sf::Texture screen_texture_;
    Framebuffer<160, 144, 4> framebuffer_;
};

#endif