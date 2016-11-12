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
		OAM(MMU& mmu);
		~OAM();

		Sprite getSprite(uint8_t idx) const;
		std::vector<Sprite> getSprites() const;

	private:
		MMU& mmu_;
	};
}

#endif // GAMEBOY_OAM_H
