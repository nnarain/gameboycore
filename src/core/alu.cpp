
#include "gameboy/alu.h"

#include "bitutil.h"

namespace gb
{
	ALU::ALU(uint8_t& flags) :
		flags_(flags)
	{
	}

	void ALU::add(uint8_t& a, uint8_t n)
	{
		bool is_half_carry = IS_HALF_CARRY(a, n);
		bool is_full_carry = IS_FULL_CARRY(a, n);

		a += n;

		setFlag(ALU::Flags::H, is_half_carry);
		setFlag(ALU::Flags::C, is_full_carry);
		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::N, false);
	}

	void ALU::add(uint16_t& hl, uint16_t n)
	{
		bool is_half_carry = IS_HALF_CARRY16(hl, n);
		bool is_full_carry = IS_FULL_CARRY16(hl, n);

		hl += n;

		setFlag(ALU::Flags::H, is_half_carry);
		setFlag(ALU::Flags::C, is_full_carry);
		setFlag(ALU::Flags::N, false);
	}

	void ALU::addr(uint16_t& sp, int8_t n)
	{
		bool is_half_carry = false;
		bool is_full_carry = false;

		// TODO: Sketchy...
//		if (n > 0)
//		{
//			is_half_carry = IS_HALF_CARRY(sp, n);
//			is_full_carry = IS_FULL_CARRY(sp, n);
//		}

		is_full_carry = ((int32_t)sp + (int32_t)n) > 0xFFFF;
		is_half_carry = IS_HALF_CARRY(sp, n);

		sp = (uint16_t)(((int)sp + (int)n) % 0xFFFF);

		setFlag(ALU::Flags::H, is_half_carry);
		setFlag(ALU::Flags::C, is_full_carry);
		setFlag(ALU::Flags::Z, false);
		setFlag(ALU::Flags::N, false);
	}

	void ALU::addc(uint8_t& a, uint8_t n)
	{
		uint8_t carry = (IS_SET(flags_, ALU::Flags::C)) ? 1 : 0;

		bool is_half_carry = IS_HALF_CARRY(a, (n + carry));
		bool is_full_carry = IS_FULL_CARRY(a, (n + carry));

		a += (n + carry);

		setFlag(ALU::Flags::H, is_half_carry);
		setFlag(ALU::Flags::C, is_full_carry);
		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::N, false);
	}

	void ALU::sub(uint8_t& a, uint8_t n)
	{
		bool is_half_borrow = IS_HALF_BORROW(a, n);
		bool is_full_borrow = IS_FULL_BORROW(a, n);

		a -= n;

		setFlag(ALU::Flags::H, is_half_borrow);
		setFlag(ALU::Flags::C, is_full_borrow);
		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::N, true);
	}

	void ALU::subc(uint8_t& a, uint8_t n)
	{
		bool is_half_borrow = IS_HALF_BORROW(a, n);
		bool is_full_borrow = IS_FULL_BORROW(a, n);

		uint8_t carry = (IS_SET(flags_, ALU::Flags::C)) ? 1 : 0;

		a -= (n + carry);

		setFlag(ALU::Flags::H, is_half_borrow);
		setFlag(ALU::Flags::C, is_full_borrow);
		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::N, true);
	}

	void ALU::anda(uint8_t& a, uint8_t n)
	{
		a &= n;

		setFlag(ALU::Flags::N, false);
		setFlag(ALU::Flags::H, true);
		setFlag(ALU::Flags::C, false);
		setFlag(ALU::Flags::Z, (a == 0));
	}

	void ALU::ora(uint8_t& a, uint8_t n)
	{
		a |= n;

		setFlag(ALU::Flags::N, false);
		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::H, false);
		setFlag(ALU::Flags::C, false);
	}

	void ALU::xora(uint8_t& a, uint8_t n)
	{
		a ^= n;

		setFlag(ALU::Flags::Z, (a == 0));
		setFlag(ALU::Flags::N, false);
		setFlag(ALU::Flags::H, false);
		setFlag(ALU::Flags::C, false);
	}

	void ALU::compare(uint8_t& a, uint8_t n)
	{
		bool is_half_borrow = IS_HALF_BORROW(a, n);
		bool is_full_borrow = IS_FULL_BORROW(a, n);

		uint8_t r = a - n;

		setFlag(ALU::Flags::H, is_half_borrow);
		setFlag(ALU::Flags::C, is_full_borrow);
		setFlag(ALU::Flags::Z, (r == 0));
		setFlag(ALU::Flags::N, true);
	}

	void ALU::setFlag(uint8_t mask, bool set)
	{
		if (set)
		{
			SET(flags_, mask);
		}
		else
		{
			CLR(flags_, mask);
		}
	}

	ALU::~ALU()
	{
	}
}
