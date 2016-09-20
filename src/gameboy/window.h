
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
#include "tilemap_texture.h"

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::Gameboy& gameboy) :
		window_(sf::VideoMode(800, 600), "Gameboy Emulator"),
		tileset_(gameboy.getTileRAM()),
		background_texture_(gameboy.getTileMap(), gb::TileMap::Map::BACKGROUND)
	{
		tileset_sprite_.setTexture(tileset_.getTexture());
		tileset_sprite_.setPosition(150, 50);
		tileset_sprite_.setScale(4, 4);

		background_sprite_.setTexture(background_texture_.getTexture());
		background_sprite_.setPosition(10, 10);
		background_sprite_.setScale(2, 2);
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

		window_.clear();
//		tileset_.update();
//		background_texture_.update();

		//window_.draw(tileset_sprite_);
		window_.draw(background_sprite_);
		window_.display();
	}

	void updateTextures()
	{
		background_texture_.update();
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

	TileMapTexture background_texture_;
	sf::Sprite background_sprite_;

};


#endif // EMULATOR_WINDOW_H

