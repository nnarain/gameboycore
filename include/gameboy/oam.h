#ifndef GAMEBOY_OAM_H
#define GAMEBOY_OAM_H

#include "gameboy/mmu.h"
#include "gameboy/memorymap.h"
#include "gameboy/sprite.h"

#include <vector>

namespace gb
{
	/**
		\brief Access Gameboy Object Attribute Memory
	*/
	class OAM
	{
	public:
		OAM(MMU& mmu) : mmu_{ mmu }
		{
		}

		Sprite getSprite(uint8_t idx) const
		{
			auto sprite_base = memorymap::OAM_START + (idx * sizeof(Sprite));

			Sprite sprite;
			sprite.y    = mmu_.read(sprite_base + 0);
			sprite.x    = mmu_.read(sprite_base + 1);
			sprite.tile = mmu_.read(sprite_base + 2);
			sprite.attr = mmu_.read(sprite_base + 3);

			return sprite;
		}

		std::vector<Sprite> getSprites() const
		{
			std::vector<Sprite> sprites;

			const auto num_sprites = 40;
			for (auto i = 0; i < num_sprites; ++i)
			{
				sprites.push_back(getSprite(i));
			}

			return sprites;
		}

		~OAM()
		{
		}

	private:
		MMU& mmu_;
	};
}

#endif // GAMEBOY_OAM_H