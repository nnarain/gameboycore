
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
#include "oam_texture.h"

/**
	\brief Emulator Window
*/
class Window
{
public:
	Window(gb::Gameboy& gameboy) :
		window_(sf::VideoMode(325, 300), "Tis Emulator"),
		tileram_{gameboy.getTileRAM()},
		tileset_(gameboy.getTileRAM()),
		background_texture_(gameboy.getTileMap(), gb::TileMap::Map::BACKGROUND),
		oam_texture_{gameboy.getOAM()}
	{
		tileset_sprite_.setTexture(tileset_.getTexture());
		tileset_sprite_.setPosition(150, 50);
		tileset_sprite_.setScale(4, 4);

		background_sprite_.setTexture(background_texture_.getTexture());
		background_sprite_.setPosition(0, 0);
		background_sprite_.setScale(2, 2);

		oam_sprite_.setTexture(oam_texture_.getTexture());
		oam_sprite_.setPosition(0, 0);
		oam_sprite_.setScale(2, 2);
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
		window_.draw(background_sprite_);
		window_.draw(oam_sprite_);
		window_.display();
	}

	void updateTextures()
	{
		background_texture_.update();
		oam_texture_.update(tileram_);
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

	gb::TileRAM tileram_;
	
	TilesetTexture tileset_;
	sf::Sprite tileset_sprite_;

	TileMapTexture background_texture_;
	sf::Sprite background_sprite_;

	OAMTexture oam_texture_;
	sf::Sprite oam_sprite_;
};


#endif // EMULATOR_WINDOW_H

