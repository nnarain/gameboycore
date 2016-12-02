#include "gameboycore/link.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/interrupt_provider.h"

namespace gb
{
	/* Private Interface */

	class Link::Impl
	{
	public:

		Impl(MMU::Ptr& mmu) : mmu_(mmu)
		{
			// serial byte handlers
			mmu->addReadHandler(memorymap::SB_REGISTER, std::bind(&Impl::sbReadHandler, this, std::placeholders::_1));
			mmu->addWriteHandler(memorymap::SB_REGISTER, std::bind(&Impl::sbWriteHandler, this, std::placeholders::_1, std::placeholders::_2));

			// control callback
			mmu->addWriteHandler(memorymap::SC_REGISTER, std::bind(&Impl::control, this, std::placeholders::_1, std::placeholders::_2));
		}

		~Impl()
		{
		}

		void update(uint8_t cycles)
		{
		}

		void control(uint8_t value, uint16_t addr)
		{
		}

		void sbWriteHandler(uint8_t value, uint16_t addr)
		{
		}

		uint8_t sbReadHandler(uint16_t addr)
		{
			return 0;
		}

		void write(uint8_t* buffer, std::size_t size)
		{
		}

		void setOutboundCallback(const SendCallback& callback)
		{
			send_callback_ = callback;
		}

	private:
		MMU::Ptr& mmu_;

		//! Sending data outbound to hosts
		SendCallback send_callback_;
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

	void Link::setOutboundCallback(const SendCallback& callback)
	{
		impl_->setOutboundCallback(callback);
	}

	Link::~Link()
	{
		delete impl_;
	}
}