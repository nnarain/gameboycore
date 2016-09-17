/**
	@author Natesh Narain <nnaraindev@gmail.com>
	@date Sept 15 2016
*/

#ifndef EMULATOR_TILEMAP_TEXTURE_H
#define EMUALTOR_TILEMAP_TEXTURE_H

#include <SFML/Graphics.hpp>

#include <gameboy/tilemap.h>

#include <stdexcept>

#include "texture_buffer.h"

/**
	\brief Wrapper for Background Map data
*/
class TileMapTexture
{
public:

	TileMapTexture(gb::TileMap& tilemap, gb::TileMap::Map map) :
		tilemap_(tilemap),
		map_(map)
	{
		if (!texture_.create(256, 256))
			throw std::runtime_error("Unable to create texture");
	}

	void update()
	{
		static sf::Color palette[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{ 96,  96,  96, 255 },
			{ 0,   0,   0, 255 }
		};

		gb::TileMap::Iterator iter = tilemap_.begin(map_);
		gb::TileMap::Iterator end  = tilemap_.end(map_);

		TextureBuffer texture_buffer(256, 256, 255);

		int tile_x = 0; // pixel offset x for tile
		int tile_y = 0; // pixel offset y for tile
		int tile_count = 0; // count of tiles per row

		for (; iter != end; ++iter)
		{
			gb::Tile tile = *iter;
			texture_buffer.write(tile, tile_x, tile_y, palette);

			tile_x += 8;
			tile_count++;
			if (tile_count >= 32)
			{
				tile_y += 8;
				tile_x = 0;
				tile_count = 0;
			}
		}

		texture_.update(texture_buffer.get());
	}

	sf::Texture& getTexture()
	{
		return texture_;
	}

private:
	sf::Texture texture_;

	gb::TileMap tilemap_;
	gb::TileMap::Map map_;
};

#endif
