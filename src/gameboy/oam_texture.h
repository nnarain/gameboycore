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
			auto tile = tileram.getTile(sprite.tile);
			texture_buffer.write(tile, sprite.x, sprite.y, palette);
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
	gb::OAM& oam_;
};

#endif
