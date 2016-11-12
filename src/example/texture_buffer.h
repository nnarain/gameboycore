
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_TEXTURE_BUFFER_H
#define EMULATOR_TEXTURE_BUFFER_H

#include <vector>
#include <cstdint>

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
	void write(unsigned int x, unsigned int y, PixelT pixel)
	{
		const unsigned int pixels_per_row = width_;

		unsigned int byte_offset = ((y * pixels_per_row) + x) * PIXEL_SIZE;

		buffer_[byte_offset + 0] = pixel.r;
		buffer_[byte_offset + 1] = pixel.g;
		buffer_[byte_offset + 2] = pixel.b;
		buffer_[byte_offset + 3] = pixel.a;
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