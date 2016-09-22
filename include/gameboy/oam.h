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
		OAM(MMU& mmu) : mmu_{mmu}
		{
		}

		Sprite getSprite(uint8_t idx) const
		{
			auto ptr = mmu_.getptr(memorymap::OAM_START + (idx * sizeof(Sprite)));

			Sprite sprite;
			sprite.y    = ptr[0];
			sprite.x    = ptr[1];
			sprite.tile = ptr[2];
			sprite.attr = ptr[3];

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