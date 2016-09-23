#ifndef EMULATOR_OAM_TEXTURE_H
#define EMULATOR_OAM_TEXTURE_H

#include <gameboy/tileram.h>
#include <gameboy/tile.h>
#include <gameboy/oam.h>
#include <gameboy/sprite.h>

#include <SFML/Window.hpp>

#include "texture_buffer.h"

class OAMTexture
{
public:

	OAMTexture(gb::OAM& oam) : oam_{oam}
	{
		if (!texture_.create(256, 256))
			throw std::runtime_error("Could not create texture");
	}

	void update(const gb::TileRAM& tileram)
	{
		static sf::Color palette[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{ 96,  96,  96, 255 },
			{ 0,   0,   0, 255 }
		};

		TextureBuffer texture_buffer{ 256, 256, 0 };

		auto sprites = oam_.getSprites();

		for (auto sprite : sprites)
		{
			auto tile = tileram.getSpriteTile(sprite);

			if (sprite.x == 0 || sprite.y == 0) continue;

			uint8_t x_coord = sprite.x - 8;
			uint8_t y_coord = sprite.y - 16;
			texture_buffer.write(tile, x_coord, y_coord, palette);
		}

		texture_.update(texture_buffer.get());
	}

	sf::Texture& getTexture()
	{
		return texture_;
	}

	~OAMTexture()
	{
	}

private:
	sf::Texture texture_;
	gb::OAM oam_;
};

#endif
