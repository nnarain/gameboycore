#include "gameboycore/link.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/interrupt_provider.h"

#include "bitutil.h"

#include <queue>

namespace gb
{
	/* Private Interface */

	class Link::Impl
	{
	public:

		Impl(MMU::Ptr& mmu) : 
			mmu_(mmu),
			control_(mmu->get(memorymap::SC_REGISTER)),
			serial_interrupt_{ *mmu.get(), InterruptProvider::Interrupt::SERIAL },
			shift_clock_(0),
			shift_counter_(0),
			shift_clock_rate_(0),
			byte_to_recieve_(0),
			byte_to_transfer_(0)
		{
			// serial byte handlers
			mmu->addReadHandler(memorymap::SB_REGISTER, std::bind(&Impl::recieveHandler, this, std::placeholders::_1));
			mmu->addWriteHandler(memorymap::SB_REGISTER, std::bind(&Impl::sendHandler, this, std::placeholders::_1, std::placeholders::_2));

			// control callback
			mmu->addWriteHandler(memorymap::SC_REGISTER, std::bind(&Impl::control, this, std::placeholders::_1, std::placeholders::_2));
		}

		~Impl()
		{
		}

		void update(uint8_t cycles)
		{
			if (!isTransferring()) return;

			// if using internal shift clock, run clocking logic
			if (isUsingInternalClock())
			{
				internalClock(cycles);
			}
			else
			{
				// transferring in external clock mode, signal transfer ready
				signalReady();
			}
		}

		void internalClock(uint8_t cycles)
		{
			// increment shift clock
			shift_clock_ += cycles;

			if (shift_clock_ >= shift_clock_rate_)
			{
				shift_clock_ -= shift_clock_rate_;

				shift_counter_++;

				if (shift_counter_ == 8)
				{
					// signal to the host system that this core is ready to do the transfer
					signalReady();

					shift_counter_ = 0;
				}
			}
		}

		void control(uint8_t value, uint16_t addr)
		{
			if (!isTransferring())
			{
				shift_clock_rate_ = getTransferRate(value);
				control_ = value;
			}
			else
			{
				FORCE(control_, 0x03, value);
			}
		}

		void sendHandler(uint8_t value, uint16_t addr)
		{
			if (!isTransferring())
			{
				byte_to_transfer_ = value;
			}
		}

		uint8_t recieveHandler(uint16_t addr)
		{
			return byte_to_recieve_;
		}

		/**
			Data into the core
		*/
		void recieve(uint8_t byte)
		{
			// recieve the byte
			byte_to_recieve_ = byte;
			// set serial interrupt
			serial_interrupt_.set();
			// clear transfer flag
			CLR(control_, memorymap::SC::TRANSFER);
		}

		void setSendCallback(const SendCallback& callback)
		{
			send_callback_ = callback;
		}

		void setOpponentReadyCallback(const OpponentReadyCallback& callback)
		{
			opponent_ready_ = callback;
		}

		void setReadyCallback(const ReadyCallback& callback)
		{
			ready_callback_ = callback;
		}

	private:

		bool isTransferring()
		{
			return IS_SET(control_, memorymap::SC::TRANSFER) != 0;
		}

		bool isUsingInternalClock()
		{
			return IS_SET(control_, memorymap::SC::CLOCK_MODE);
		}

		int getTransferRate(uint8_t sc)
		{
			// TODO: CGB speed modes
			return 8192;
		}

		bool isOpponentReady()
		{
			return (opponent_ready_) ? opponent_ready_() : false;
		}

		void signalReady()
		{
			if (ready_callback_)
				ready_callback_(byte_to_transfer_, getLinkMode());
		}

		Mode getLinkMode()
		{
			return IS_SET(control_, memorymap::SC::CLOCK_MODE) ? Mode::INTERNAL : Mode::EXTERNAL;
		}

	private:
		MMU::Ptr& mmu_;

		//! Serial Control Register
		uint8_t& control_;

		//! Recieve queue
		std::queue<uint8_t> recieve_queue_;
		//! Send queue
		uint8_t byte_to_transfer_;
		//!
		uint8_t byte_to_recieve_;

		//! Sending data outbound to hosts
		SendCallback send_callback_;
		//!
		OpponentReadyCallback opponent_ready_;
		//!
		ReadyCallback ready_callback_;

		//! Serial interrupt provider
		InterruptProvider serial_interrupt_;

		//! Internal Timer
		int shift_clock_;
		//!
		int shift_counter_;
		//! Transfer rate
		int shift_clock_rate_;
	};

	/* Public Interface */

	Link::Link(MMU::Ptr& mmu) :
		impl_(new Impl(mmu))
	{
	}

	void Link::update(uint8_t cycles)
	{
		impl_->update(cycles);
	}

	void Link::recieve(uint8_t byte)
	{
		impl_->recieve(byte);
	}

	void Link::setSendCallback(const SendCallback& callback)
	{
		impl_->setSendCallback(callback);
	}

	void Link::setOpponentReadyCallback(const OpponentReadyCallback& callback)
	{
		impl_->setOpponentReadyCallback(callback);
	}

	void Link::setReadyCallback(const ReadyCallback& callback)
	{
		impl_->setReadyCallback(callback);
	}

	Link::~Link()
	{
		delete impl_;
	}
}