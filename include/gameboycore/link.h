/**
	\file link.h
	\brief Link port emulation
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 30 2016
*/

#ifndef GAMEBOYCORE_LINK_H
#define GAMEBOYCORE_LINK_H

#include "gameboycore/gameboycore_api.h"
#include "gameboycore/mmu.h"

#include <cstdint>
#include <memory>
#include <functional>

namespace gb
{
	/**
		\class Link
		\brief Emulate link port
		\ingroup API
	*/
	class GAMEBOYCORE_API Link
	{
	public:
		//! Smart pointer type
		using Ptr = std::unique_ptr<Link>;

		//! 
		using SendCallback = std::function<void(uint8_t)>;

	public:
		Link(MMU::Ptr& mmu);
		~Link();

		void update(uint8_t cycles);

		/**
			Write a byte buffer into the core
		*/
		void write(uint8_t* buffer, std::size_t length);

		/**
		
		*/
		void setOutboundCallback(const SendCallback& callback);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif
