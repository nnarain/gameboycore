#pragma once

#include "ui/views/view.hpp"

#include <gameboycore/gameboycore.h>

#include <imgui.h>
#include <imgui_memory_editor/imgui_memory_editor.h>

class MemoryView : public View
{
public:
    MemoryView(gb::GameboyCore& core);
    ~MemoryView() = default;

    virtual std::string name() override;
    virtual void render() override;

private:
    static uint8_t readFn(const uint8_t* mem, size_t offset);
    static void writeFn(uint8_t* mem, size_t offset, uint8_t value);

    static gb::GameboyCore* g_core_;

    void drawAnnotation();

    MemoryEditor editor_;
};
