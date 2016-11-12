#ifndef GAMEBOYCORE_OAM_H
#define GAMEBOYCORE_OAM_H

#include "gameboycore/mmu.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/sprite.h"

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

#endif // GAMEBOYCORE_OAM_H
