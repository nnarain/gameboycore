#ifndef EMULATOR_TILESET_TEXTURE_H
#define EMULATOR_TILESET_TEXTURE_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <gameboy/tileram.h>

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
		std::vector<sf::Uint8> pixel_data(120 * 120 * 4, 255);

		std::vector<gb::Tile> tiles = tile_ram_.getTiles();

		int tile_x = 0;
		int tile_y = 0;
		int tile_count = 0;

		for (gb::Tile& tile : tiles)
		{
			int pixel = 0;
			for (int row = 0; row < 8; ++row)
			{
				for (int col = 0; col < 8; ++col)
				{
					sf::Color color = getColor(tile.color[pixel++]);
					writePixel(pixel_data, tile_x + col, tile_y + row, color);
				}
			}

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
		texture_.update(&pixel_data[0]);
	}

	sf::Texture& getTexture()
	{
		return texture_;
	}

private:
	void writePixel(std::vector<sf::Uint8>& pixels, int x, int y, sf::Color c)
	{
		const unsigned int pixels_per_row = 120; // pixels per row

		int byte_offset = ((y * pixels_per_row) + x) * 4;

		pixels[byte_offset + 0] = c.r;
		pixels[byte_offset + 1] = c.g;
		pixels[byte_offset + 2] = c.b;
		pixels[byte_offset + 3] = c.a;
	}

	sf::Color getColor(uint8_t idx)
	{
		static sf::Color colors[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{  96,  96,  96, 255 },
			{   0,   0,   0, 255 }
		};

		return colors[idx];
	}

private:
	gb::TileRAM tile_ram_;

	sf::Texture texture_;
};

#endif // EMULATOR_TILESET_TEXTURE_H
