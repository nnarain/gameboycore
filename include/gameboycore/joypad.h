
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_JOYPAD_H
#define GAMEBOYCORE_JOYPAD_H

#include "gameboycore/gameboycore_api.h"
#include "gameboycore/mmu.h"

#include <functional>
#include <memory>

namespace gb
{
	class GAMEBOYCORE_API Joy
	{
	public:
		enum class Key
		{
			RIGHT  = 0,
			LEFT   = 1,
			UP     = 2,
			DOWN   = 3,
			A      = 4,
			B      = 5,
			SELECT = 6,
			START  = 7
		};

		using Ptr = std::shared_ptr<Joy>;

		Joy(MMU& mmu);
		~Joy();

		void press(Key key);
		void release(Key key);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif // GAMEBOY_JOYPAD_H
