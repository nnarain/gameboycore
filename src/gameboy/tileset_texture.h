#ifndef EMULATOR_TILESET_TEXTURE_H
#define EMULATOR_TILESET_TEXTURE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

#include "texture_buffer.h"

/**
	\brief Create and update texture of the gameboy's tileset
*/
class TilesetTexture
{
public:
	TilesetTexture(gb::TileRAM& tile_ram) :
		tile_ram_(tile_ram)
	{
		if (!texture_.create(120, 120))
			throw std::runtime_error("Could not create texture");
	}

	~TilesetTexture()
	{
	}

	void update()
	{
		static sf::Color palette[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{ 96,  96,  96, 255 },
			{ 0,   0,   0, 255 }
		};

		TextureBuffer texture_buffer(120, 120, 255);
		std::vector<gb::Tile> tiles = tile_ram_.getTiles();

		int tile_x     = 0; // pixel offset x for tile
		int tile_y     = 0; // pixel offset y for tile
		int tile_count = 0; // count of tiles per row

		for (gb::Tile& tile : tiles)
		{
			texture_buffer.write(tile, tile_x, tile_y, palette);

			tile_x += 8;
			tile_count++;
			if (tile_count >= 15)
			{
				tile_y += 8;
				tile_x = 0;
				tile_count = 0;
			}
		}

		// update the tileset texture
		texture_.update((sf::Uint8*)texture_buffer.get());
	}

	sf::Texture& getTexture()
	{
		return texture_;
	}

private:
	gb::TileRAM tile_ram_;

	sf::Texture texture_;
};

#endif // EMULATOR_TILESET_TEXTURE_H
