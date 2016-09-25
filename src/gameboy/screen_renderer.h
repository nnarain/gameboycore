
/**
	\author Natesh Narain
	\data Sept 24 2016
*/

#ifndef EMULATOR_SCREEN_RENDERER_H
#define EMULATOR_SCREEN_RENDERER_H

#include <gameboy/gameboy.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <stdexcept>

#include "texture_buffer.h"

/**
	\brief Render Gameboy screen
*/
class ScreenRenderer
{
public:
	ScreenRenderer(gb::Gameboy& gameboy) :
		lcd_{gameboy.getLCDController()},
		tilemap_{gameboy.getTileMap()},
		tileram_{gameboy.getTileRAM()},
		oam_{gameboy.getOAM()}
	{
		if (!screen_texture_.create(256, 256))
			throw std::runtime_error("Could not create texture");

		screen_sprite_.setTexture(screen_texture_);
		screen_sprite_.setScale(2, 2);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(screen_sprite_);
	}

	void update()
	{
		// create a buffer for the new pixel data
		TextureBuffer buffer(256, 256, 0);

		// grab flags for what maps are being drawn
		bool background_on     = lcd_.isBackgroundEnabled();
		bool window_overlay_on = lcd_.isWindowOverlayEnabled();
		bool sprites_on        = lcd_.isSpritesEnabled();

		if (background_on)
		{
			auto tiles = tilemap_.getMapData(tileram_, gb::TileMap::Map::BACKGROUND);
			drawBackgroundData(buffer, tiles);
		}

		if (window_overlay_on)
		{
			auto tiles = tilemap_.getMapData(tileram_, gb::TileMap::Map::WINDOW_OVERLAY);
			drawBackgroundData(buffer, tiles);
		}

		if (sprites_on)
		{
			auto sprites = oam_.getSprites();
			std::reverse(sprites.begin(), sprites.end());

			for (auto sprite : sprites)
			{
				buffer.write(sprite, tileram_);
			}
		}

		screen_texture_.update(buffer.get());
	}

	~ScreenRenderer()
	{
	}

private:

	void drawBackgroundData(TextureBuffer& buffer, std::vector<gb::Tile>& tiles)
	{
		static sf::Color palette[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{ 96,  96,  96, 255 },
			{ 0,   0,   0, 255 }
		};

		auto tile_x     = 0; // pixel offset x for tile
		auto tile_y     = 0; // pixel offset y for tile
		auto tile_count = 0; // count of tiles per row

		for (auto tile : tiles)
		{
			buffer.write(tile, tile_x, tile_y, palette);

			tile_x += 8;
			tile_count++;
			if (tile_count >= 32)
			{
				tile_y += 8;
				tile_x = 0;
				tile_count = 0;
			}
		}
	}

private:
	sf::Sprite screen_sprite_;
	sf::Texture screen_texture_;

	gb::LCDController& lcd_; // LCD proxy?
	gb::TileMap tilemap_;
	gb::TileRAM tileram_;
	gb::OAM     oam_;
};

#endif // EMULATOR_SCREEN_RENDERER_H
