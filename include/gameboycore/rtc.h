/**
	\file rtc.h
	\brief Real Time Clock Emulation
	\author Natesh Narain
*/

#ifndef GAMEBOYCORE_RTC_H
#define GAMEBOYCORE_RTC_H

#include <array>
#include <ctime>

namespace gb
{
	namespace detail
	{
		/**
			\class RTC
			\brief Real Time Clock
			\ingroup MBC
		*/
		class RTC
		{
		private:
			static constexpr uint8_t REGISTER_BASE = 0x08;
			
			enum Registers
			{
				SECONDS_REGISTER = 0,
				MINUTES_REGISTER,
				HOURS_REGISTER,
				DAY_LSB_REGISTER,
				DAY_MSB_REGISTER
			};

		public:
			RTC() :
				enabled_(false)
			{
			}

			~RTC()
			{
			}

			uint8_t get() const
			{
				std::time_t time = std::time(0);
				std::tm* now = std::localtime(&time);

				switch (selected_)
				{
				case SECONDS_REGISTER:
					return now->tm_sec;
				case MINUTES_REGISTER:
					return now->tm_min;
				case HOURS_REGISTER:
					return now->tm_hour;
				default:
					return 0;
				}
			}

			void select(uint8_t reg)
			{
				selected_ = reg - REGISTER_BASE;
			}

			void setEnable(bool enable)
			{
				enabled_ = enable;
			}

			bool isEnabled() const
			{
				return enabled_;
			}

		private:
			bool enabled_;
			uint8_t selected_;
		};
	}
}

#endif // GAMEBOYCORE_RTC_H
