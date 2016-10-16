#include "gameboy/oam.h"
#include "bitutil.h"

namespace gb
{
	OAM::OAM(MMU& mmu) : 
		mmu_(mmu),
		lcdc_(mmu.get(memorymap::LCDC_REGISTER))
	{
	}

	Sprite OAM::getSprite(uint8_t idx) const
	{
		// get location of sprite in memory
		auto sprite_base = memorymap::OAM_START + (idx * 4);

		// read OAM attributes from OAM table
		Sprite sprite;
		sprite.y    = mmu_.read(sprite_base + 0);
		sprite.x    = mmu_.read(sprite_base + 1);
		sprite.tile = mmu_.read(sprite_base + 2);
		sprite.attr = mmu_.read(sprite_base + 3);

		return sprite;
	}

	std::vector<Sprite> OAM::getSprites() const
	{
		// check if sprites are 8x16 or 8x8
		const bool mode_8x16 = IS_BIT_SET(lcdc_, 2) != 0;

		std::vector<Sprite> sprites;

		const auto num_sprites = 40;
		for (auto i = 0; i < num_sprites; ++i)
		{
			auto sprite = getSprite(i);
			sprites.push_back(sprite);

			if (mode_8x16)
			{
				// if in 8x16 create another sprite with the following tile number and offset y coordinate
				auto sprite2 = sprite;
				sprite2.tile++;
				sprite2.y += 8;
			}
		}

		return sprites;
	}

	OAM::~OAM()
	{
	}
}