
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_TEXTURE_BUFFER_H
#define EMULATOR_TEXTURE_BUFFER_H

#include <vector>
#include <cstdint>

#include "gameboy/tileram.h"
#include "gameboy/tile.h"
#include "gameboy/sprite.h"

/**
	\brief	Write Colors to a Pixel Buffer
*/
class TextureBuffer
{
public:
	const unsigned int PIXEL_SIZE = 4;

public:
	/**
		Initialize a Texture Buffer of width x height in pixels.
	*/
	TextureBuffer(unsigned int width, unsigned int height, unsigned int fill = 255) :
		width_(width),
		height_(height),
		buffer_(width * height * PIXEL_SIZE, fill)
	{
	}

	template<typename PixelT>
	void write(gb::Tile& tile, unsigned int x, unsigned int y, PixelT* palette)
	{
		unsigned int pixel = 0;

		for (unsigned int row = 0; row < 8; ++row)
		{
			for (unsigned int col = 0; col < 8; ++col)
			{
				PixelT& color = palette[tile.color[pixel++]];
				write(x + col, y + row, color);
			}
		}
	}

	template<typename PixelT>
	void write(unsigned int x, unsigned int y, PixelT pixel)
	{
		const unsigned int pixels_per_row = width_;

		unsigned int byte_offset = ((y * pixels_per_row) + x) * PIXEL_SIZE;

		buffer_[byte_offset + 0] = pixel.r;
		buffer_[byte_offset + 1] = pixel.g;
		buffer_[byte_offset + 2] = pixel.b;
		buffer_[byte_offset + 3] = pixel.a;
	}

	void write(gb::Sprite sprite, gb::TileRAM tileram)
	{
		static sf::Color palette[] = {
			{ 255, 255, 255, 255 },
			{ 192, 192, 192, 255 },
			{ 96,  96,  96, 255 },
			{ 0,   0,   0, 255 }
		};

		auto tile = tileram.getSpriteTile(sprite);

		uint8_t x_coord = sprite.x - 8;
		uint8_t y_coord = sprite.y - 16;

		// do not render this sprite if out of bounds
		if (x_coord == 0 || x_coord >= 168) return;
		if (y_coord == 0 || y_coord >= 160) return;

		// TODO: sprite priority
		write(tile, x_coord, y_coord, palette);
	}

	uint8_t* get()
	{
		return &buffer_[0];
	}

	~TextureBuffer()
	{
	}

private:
	const unsigned int width_;
	const unsigned int height_;
	std::vector<uint8_t> buffer_;

};

#endif // EMULATOR_TEXTURE_BUFFER_H