
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef ALU_H
#define ALU_H

#include <cstdint>

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

	private:
		uint8_t& flags_;
	};

}
#endif // ALU_H