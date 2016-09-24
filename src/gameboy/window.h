
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

#include <stdexcept>

#include "screen_renderer.h"

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::Gameboy& gameboy) :
		window_(sf::VideoMode(325, 300), "Tis Emulator"),
		screen_renderer_{gameboy}
	{
	}

	void update()
	{
		// pump event loop
		sf::Event event;
		while (window_.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window_.close();
				break;
				// TODO: add other enum values here
			}
		}

		window_.clear(sf::Color(255, 0, 0, 255));
		screen_renderer_.draw(window_);
		window_.display();
	}

	void updateTextures()
	{
		screen_renderer_.update();
	}

	bool isOpen()
	{
		return window_.isOpen();
	}

	~Window()
	{
	}

private:



private:
	sf::RenderWindow window_;
	ScreenRenderer screen_renderer_;
};


#endif // EMULATOR_WINDOW_H

