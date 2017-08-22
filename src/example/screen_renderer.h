
/**
	\author Natesh Narain
	\data Sept 24 2016
*/

#ifndef EMULATOR_SCREEN_RENDERER_H
#define EMULATOR_SCREEN_RENDERER_H

#include <gameboycore/gameboycore.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <queue>
#include <mutex>
#include <stdexcept>

#include "texture_buffer.h"

/**
	\brief Render Gameboy screen
*/
class ScreenRenderer
{
	static constexpr auto TILES_PER_ROW = 20;
	static constexpr auto TILES_PER_COL = 18;
	static constexpr auto WIDTH         = TILES_PER_ROW * 8;
	static constexpr auto HEIGHT        = TILES_PER_COL * 8;

	struct RenderData
	{
		gb::GPU::Scanline pixels;
		int line;
	};

public:
	ScreenRenderer(unsigned int display_width = WIDTH, unsigned int display_height = HEIGHT) :
		frame_buffer_(WIDTH, HEIGHT, 0),
		draw_rect_(sf::Vector2f((float)display_width, (float)display_height))
	{
		if (!screen_texture_.create(WIDTH, HEIGHT))
			throw std::runtime_error("Could not create texture");

		draw_rect_.setTexture(&screen_texture_);
	}

	void draw(sf::RenderWindow& window)
	{
		updateTexture();
		window.draw(draw_rect_);
	}

	void gpuCallback(const gb::GPU::Scanline& scanline, int line)
	{
		std::lock_guard<std::mutex> lock(mutex_);

		RenderData data;
		data.pixels = scanline;
		data.line = line;

		lines_queue_.push(data);
	}

	void updateTexture()
	{
		while (lines_queue_.size())
		{
			std::lock_guard<std::mutex> lock(mutex_);

			auto col = 0;

			auto data = lines_queue_.front();
			lines_queue_.pop();

			for (const auto& pixel : data.pixels)
			{
				sf::Color color;
				color.r = pixel.r;
				color.g = pixel.g;
				color.b = pixel.b;
				color.a = 255;

				frame_buffer_.write(col++, data.line, color);
			}

			screen_texture_.update(frame_buffer_.get());
		}
	}

	void setDrawRectY(float y)
	{
		draw_rect_.setPosition(draw_rect_.getPosition().x, y);
	}

	void setDisplaySize(const sf::Vector2u& size)
	{
		draw_rect_.setSize(static_cast<sf::Vector2f>(size));
	}

	void setDisplaySize(unsigned int w, unsigned int h)
	{
		draw_rect_.setSize(sf::Vector2f((float)w, (float)h));
	}

	~ScreenRenderer()
	{
	}

private:
	sf::RectangleShape draw_rect_;
	sf::Texture screen_texture_;
	TextureBuffer frame_buffer_;

	std::queue<RenderData> lines_queue_;
	std::mutex mutex_;
};

#endif // EMULATOR_SCREEN_RENDERER_H
