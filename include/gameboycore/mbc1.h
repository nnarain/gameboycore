
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\brief Memory Back Controller 1
	\date Oct 11 2016
*/

#ifndef GAMEBOYCORE_MBC1_H
#define GAMEBOYCORE_MBC1_H

#include "gameboycore/mbc.h"

#include <vector>
#include <cstring>

namespace gb
{
	namespace detail
	{
		/**
			\class MBC1
			\brief Memory Bank Controller 1
		*/
		class MBC1 : public MBC
		{
		private:

			//! RAM or ROM bank switching mode
			enum class MemoryMode
			{
				ROM = 0, RAM = 1 ///< determines how address range $4000 - $5000 is used
			};

		public:
			MBC1(uint8_t* rom, uint32_t size, uint8_t rom_size, uint8_t ram_size);

			virtual void write(uint8_t value, uint16_t addr);

			virtual uint8_t read(uint16_t addr) const;

			virtual uint8_t& get(uint16_t addr);

			virtual uint8_t* getptr(uint16_t addr);

			virtual void control(uint8_t value, uint16_t addr);

		private:
			void selectRomBank(uint8_t lo, uint8_t hi);
			void selectRamBank(uint8_t ram_bank_number);

			void loadROM(uint8_t* rom, uint32_t size, uint8_t rom_size);
			void loadRAM(uint8_t ram_size);

		private:
			// TODO: these could be protected member of MBC base class
			MBC::Bank  rom0_;            ///< $0000 - $3FFF
			MBC::Banks switchable_rom_;  ///< $4000 - $7FFF
			MBC::Bank  ram1_;            ///< $8000 - $9FFF
			MBC::Banks switchable_ram1_; ///< $A000 - $BFFF
			MBC::Bank  ram2_;            ///< $C000 - $CFFF
			MBC::Banks switchable_ram2_; ///< $D000 - $DFFF (Switchable in CGB mode Only)
			MBC::Bank  ram3_;            ///< $E000 - $FFFF

			unsigned int rom_idx_;
			unsigned int rom_bank_lower_bits_; // bit 0 - 4
			unsigned int rom_bank_upper_bits_; // bit 5 and 6

			unsigned int ram_idx_;

			MemoryMode mode_;
		};
	}
}

#endif
