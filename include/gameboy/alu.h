
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef ALU_H
#define ALU_H

#include <stdint.h>

/**
	Contains Math and Logical operation
*/
namespace gb
{
	class ALU
	{
	public:
		enum Flags
		{
			Z = 1 << 7,
			N = 1 << 6,
			H = 1 << 5,
			C = 1 << 4
		};

	public:
		ALU(uint8_t& flags);
		~ALU();

		/**
			ADD
		*/
		void add(uint8_t& a, uint8_t n);

		/**
			ADC
		*/
		void addc(uint8_t& a, uint8_t n);

		/**
			SUB
		*/
		void sub(uint8_t& a, uint8_t n);

		/**
			SUBC
		*/
		void subc(uint8_t& a, uint8_t n);

		/**
			AND
		*/
		void anda(uint8_t& a, uint8_t n);

		/**
			OR
		*/
		void ora(uint8_t& a, uint8_t n);

		/**
			XOR
		*/
		void xora(uint8_t& a, uint8_t n);

		/**
			Compare
		*/
		void compare(uint8_t& a, uint8_t n);

	private:
		uint8_t& flags_;
	};

}
#endif // ALU_H
