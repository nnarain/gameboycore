#include "gameboycore/oam.h"
#include "bitutil.h"

namespace gb
{
	OAM::OAM(MMU& mmu) : 
		mmu_(mmu)
	{
	}

	Sprite OAM::getSprite(uint8_t idx) const
	{
		// get location of sprite in memory
		auto sprite_base = memorymap::OAM_START + (idx * 4);

		auto ptr = mmu_.getptr(sprite_base);

		// read OAM attributes from OAM table
		Sprite sprite;
		sprite.y    = ptr[0];
		sprite.x    = ptr[1];
		sprite.tile = ptr[2];
		sprite.attr = ptr[3];

		return sprite;
	}

	std::vector<Sprite> OAM::getSprites() const
	{
		// check if sprites are 8x16 or 8x8
		auto lcdc = mmu_.read(memorymap::LCDC_REGISTER);
		const bool mode_8x16 = IS_SET(lcdc, memorymap::LCDC::OBJ_8x16) != 0;

		std::vector<Sprite> sprites;

		const auto num_sprites = 40;
		for (auto i = 0; i < num_sprites; ++i)
		{
			auto sprite = getSprite(i);
			
			if (mode_8x16)
			{
				sprite.height = 16;
			}
			else
			{
				sprite.height = 8;
			}

			sprites.push_back(sprite);
		}

		return sprites;
	}

	OAM::~OAM()
	{
	}
}