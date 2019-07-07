#include "ui/views/memory_view.hpp"
#include "debugger/annotations.hpp"

#include <imgui.h>

#include <fmt/format.h>

#include <functional>
#include <sstream>

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
    const auto& draw_region = ImGui::GetContentRegionAvail();

    const auto width = draw_region.x;
    const auto height = draw_region.y;

    const auto col_width = width / 3;

    if (ImGui::BeginChild("memory", { col_width * 2, height }))
    {
        editor_.DrawContents(nullptr, 0xFFFF + 1);
        ImGui::EndChild();
    }
    
    ImGui::SameLine();

    if (ImGui::BeginChild("annotation_window", { col_width, height }, true))
    {
        drawAnnotation();
        ImGui::EndChild();
    }
}

uint8_t MemoryView::readFn(const uint8_t* mem, size_t offset)
{
    return g_core_->readMemory(offset);
}

void MemoryView::writeFn(uint8_t* mem, size_t offset, uint8_t value)
{
    g_core_->writeMemory(offset, (uint16_t)value);
}

void MemoryView::drawAnnotation()
{
    // Fetch selected value
    const auto address = editor_.DataEditingAddr;
    const auto mem_value = g_core_->readMemory(static_cast<uint16_t>(address));

    const auto annotation = utils::annotateIO(address, mem_value);

    std::stringstream ss;

    for (const auto& a : annotation.annotations)
    {
        const auto& range = std::get<0>(a);
        const auto& desc = std::get<1>(a);
        const auto& value = std::get<2>(a);

        if (range.start == -1 && range.end == -1)
        {
            ss << fmt::format("* {} {}", desc, value);
        }
        else if (range.start == range.end)
        {
            ss << fmt::format("* {}: {} {}", range.start, desc, value);
        }
        else
        {
            ss << fmt::format("* {}..{}: {} {}", range.start, range.end, desc, value);
        }

        ss << "\n";
    }

    const auto text = fmt::format("{}\n{}", annotation.io_description, ss.str());
    ImGui::Text("%s", text.c_str());
}
