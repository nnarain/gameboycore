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

			// increment shift clock
			shift_clock_ += cycles;

			if (shift_clock_ >= shift_clock_rate_)
			{
				shift_clock_ -= shift_clock_rate_;

				shift_counter_++;

				if (shift_counter_ == 8)
				{
					if(send_callback_)
						send_callback_(byte_to_transfer_);

					if (recieve_queue_.size() > 0)
					{
						byte_to_recieve_ = recieve_queue_.front();
						recieve_queue_.pop();
					}
					else
					{
						byte_to_recieve_ = 0x00;
					}

					serial_interrupt_.set();

					shift_counter_ = 0;

					CLR(control_, memorymap::SC::TRANSFER);
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
		void write(uint8_t* buffer, std::size_t size)
		{
			for (auto i = 0u; i < size; ++i)
			{
				recieve_queue_.push(buffer[i]);
			}
		}

		int getTransferRate(uint8_t sc)
		{
			// TODO: CGB speed modes
			return 8192;
		}

		void setSendCallback(const SendCallback& callback)
		{
			send_callback_ = callback;
		}

	private:

		bool isTransferring()
		{
			return IS_SET(control_, memorymap::SC::TRANSFER) != 0;
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

	void Link::write(uint8_t* buffer, std::size_t length)
	{
		impl_->write(buffer, length);
	}

	void Link::setSendCallback(const SendCallback& callback)
	{
		impl_->setSendCallback(callback);
	}

	Link::~Link()
	{
		delete impl_;
	}
}