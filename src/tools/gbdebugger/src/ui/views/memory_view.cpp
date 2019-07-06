#include "ui/views/memory_view.hpp"

#include <imgui.h>

#include <functional>

using namespace gb;

GameboyCore* MemoryView::g_core_ = nullptr;

MemoryView::MemoryView(GameboyCore& core)
{
    // Provide custom read and write functions to the memory editor
    // Easy way to do this is provide a global GameboyCore instance to use in static functions
    g_core_ = &core;

    editor_.ReadFn = MemoryView::readFn;
    editor_.WriteFn = MemoryView::writeFn;
}

std::string MemoryView::name()
{
    return "Memory";
}

void MemoryView::render()
{
    editor_.DrawContents(nullptr, 0xFFFF + 1);
}

uint8_t MemoryView::readFn(const uint8_t* mem, size_t offset)
{
    return g_core_->readMemory(offset);
}

void MemoryView::writeFn(uint8_t* mem, size_t offset, uint8_t value)
{
    g_core_->writeMemory(offset, (uint16_t)value);
}
