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
		enum class Mode
		{
			INTERNAL, ///< Internal Clock Mode
			EXTERNAL  ///< External Clock Mode
		};

		//! Smart pointer type
		typedef std::unique_ptr<Link> Ptr;

		//! Callback to signal transfer ready status
		typedef std::function<void(uint8_t, Mode)> ReadyCallback;

	public:
		Link(MMU::Ptr& mmu);
		Link(const Link&);
		~Link();

		/**
			Update with CPU cycles elapsed
		*/
		void update(uint8_t cycles);

		/**
			Write a byte buffer into the core
		*/
		void recieve(uint8_t byte);

		/**
			Signal that this core is ready to transfer a byte
		*/
		void setReadyCallback(const ReadyCallback& callback);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif
