/*
	@author Natesh Narain <nnaraindev@gmail.com>
	@date Spet 15, 2016
*/

#ifndef GAMEBOY_TILEMAP_H
#define GAMEBOY_TILEMAP_H

#include "gameboy/tileram.h"
#include "gameboy/lcd_controller.h"
#include "gameboy/memorymap.h"

#include <cstdint>

namespace gb
{
	/**
		\brief Class that knows how to render background map data
	*/
	class TileMap
	{
	public:
		enum class Map
		{
			BACKGROUND, WINDOW_OVERLAY
		};

		class Iterator
		{
		public:

			Iterator(uint16_t begin, uint16_t end, TileRAM& tileram, const MMU& mmu) :
				current_(begin),
				end_(end),
				tileram_(tileram),
				mmu_(mmu)
			{
			}

			Tile operator*()
			{
				return tileram_.getTile(mmu_.read(current_));
			}

			Iterator& operator++()
			{
				current_++;
				return *this;
			}

			bool operator==(const Iterator& rhs)
			{
				// iterators are at the same memory location
				return this->current_ == rhs.current_;
			}

			bool operator!=(const Iterator& rhs)
			{
				return !(*this == rhs);
			}

		public:
			uint16_t current_;
			uint16_t end_;

		private:
			TileRAM tileram_;
			const MMU& mmu_;
		};

	public:

		TileMap(TileRAM& tileram, const MMU& mmu, const LCDController& lcd) : 
			tileram_(tileram),
			mmu_(mmu),
			lcd_(lcd)
		{
		}

		Iterator begin(Map map)
		{
			if (map == Map::BACKGROUND)
			{
				if (lcd_.getBackgroundMapLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return Iterator(memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return Iterator(memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
			else // map == WINDOW_OVERLAY
			{
				if (lcd_.getWindowOverlayLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return Iterator(memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return Iterator(memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
		}

		Iterator end(Map map)
		{
			if (map == Map::BACKGROUND)
			{
				if (lcd_.getBackgroundMapLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return Iterator(memorymap::BG_MAP_DATA_1_END, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return Iterator(memorymap::BG_MAP_DATA_2_END, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
			else // map == WINDOW_OVERLAY
			{
				if (lcd_.getBackgroundMapLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return Iterator(memorymap::BG_MAP_DATA_1_END, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return Iterator(memorymap::BG_MAP_DATA_2_END, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
		}

		~TileMap()
		{
		}

	private:
		TileRAM tileram_;
		const MMU& mmu_;
		const LCDController lcd_;
	};
}

#endif // GAMEBOY_TILEMAP_H
