
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

		if (is_half_carry)
			SET(flags_, ALU::Flags::H);
		else
			CLR(flags_, ALU::Flags::H);

		if (is_full_carry)
			SET(flags_, ALU::Flags::C);
		else
			CLR(flags_, ALU::Flags::C);

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		CLR(flags_, ALU::Flags::N);
	}

	void ALU::addc(uint8_t& a, uint8_t n)
	{
		bool is_half_carry = IS_HALF_CARRY(a, n);
		bool is_full_carry = IS_FULL_CARRY(a, n);

		uint8_t carry = (IS_SET(flags_, ALU::Flags::C)) ? 1 : 0;

		a += (n + carry);

		if (is_half_carry)
			SET(flags_, ALU::Flags::H);
		else
			CLR(flags_, ALU::Flags::H);

		if (is_full_carry)
			SET(flags_, ALU::Flags::C);
		else
			CLR(flags_, ALU::Flags::C);

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		CLR(flags_, ALU::Flags::N);
	}

	void ALU::sub(uint8_t& a, uint8_t n)
	{
		bool is_half_borrow = IS_HALF_BORROW(a, n);
		bool is_full_borrow = IS_FULL_BORROW(a, n);

		a -= n;

		if (is_half_borrow)
			SET(flags_, ALU::Flags::H);
		else
			CLR(flags_, ALU::Flags::H);

		if (is_full_borrow)
			SET(flags_, ALU::Flags::C);
		else
			CLR(flags_, ALU::Flags::C);

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		SET(flags_, ALU::Flags::N);
	}

	void ALU::subc(uint8_t& a, uint8_t n)
	{
		bool is_half_borrow = IS_HALF_BORROW(a, n);
		bool is_full_borrow = IS_FULL_BORROW(a, n);

		uint8_t carry = (IS_SET(flags_, ALU::Flags::C)) ? 1 : 0;

		a -= (n + carry);

		if (is_half_borrow)
			SET(flags_, ALU::Flags::H);
		else
			CLR(flags_, ALU::Flags::H);

		if (is_full_borrow)
			SET(flags_, ALU::Flags::C);
		else
			CLR(flags_, ALU::Flags::C);

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		SET(flags_, ALU::Flags::N);
	}

	void ALU::and(uint8_t& a, uint8_t n)
	{
		a &= n;

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		CLR(flags_, ALU::Flags::N);
		SET(flags_, ALU::Flags::H);
		CLR(flags_, ALU::Flags::C);
	}

	void ALU::or(uint8_t& a, uint8_t n)
	{
		a |= n;

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		CLR(flags_, ALU::Flags::N);
		CLR(flags_, ALU::Flags::H);
		CLR(flags_, ALU::Flags::C);
	}

	void ALU::xor(uint8_t& a, uint8_t n)
	{
		a ^= n;

		if (a == 0)
			SET(flags_, ALU::Flags::Z);
		else
			CLR(flags_, ALU::Flags::Z);

		CLR(flags_, ALU::Flags::N);
		CLR(flags_, ALU::Flags::H);
		CLR(flags_, ALU::Flags::C);
	}

	ALU::~ALU()
	{
	}
}