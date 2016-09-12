
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

#include <stdexcept>

#include "tileset_texture.h"

class Window
{
public:
	Window(gb::TileRAM& tile_ram) :
		window_(sf::VideoMode(250, 250), "Gameboy Emulator"),
		tileset_(tile_ram)
	{
		tileset_sprite_.setTexture(tileset_.getTexture());
		tileset_sprite_.setPosition(10, 10);
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
			}
		}

		window_.clear();

		tileset_.update();
		window_.draw(tileset_sprite_);

		window_.display();
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
	
	TilesetTexture tileset_;
	sf::Sprite tileset_sprite_;

};


#endif // EMULATOR_WINDOW_H

