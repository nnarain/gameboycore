#include "gameboy/oam.h"

namespace gb
{
	OAM::OAM(MMU& mmu) : mmu_(mmu)
	{
	}

	Sprite OAM::getSprite(uint8_t idx) const
	{
		auto sprite_base = memorymap::OAM_START + (idx * 4);

		Sprite sprite;
		sprite.y = mmu_.read(sprite_base + 0);
		sprite.x = mmu_.read(sprite_base + 1);
		sprite.tile = mmu_.read(sprite_base + 2);
		sprite.attr = mmu_.read(sprite_base + 3);

		return sprite;
	}

	std::vector<Sprite> OAM::getSprites() const
	{
		std::vector<Sprite> sprites;

		const auto num_sprites = 40;
		for (auto i = 0; i < num_sprites; ++i)
		{
			sprites.push_back(getSprite(i));
		}

		return sprites;
	}

	OAM::~OAM()
	{
	}
}