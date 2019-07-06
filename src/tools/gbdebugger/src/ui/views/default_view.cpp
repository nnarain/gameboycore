#include "ui/views/default_view.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

#include <fmt/format.h>

#include <functional>

using namespace gb;

DefaultView::DefaultView(GameboyCore& core, DebuggerInterface& debugger)
    : core_{core}
    , debugger_{debugger}
    , state_{}
{
    if (!screen_texture_.create(framebuffer_.width(), framebuffer_.height()))
    {
        throw std::runtime_error("Could not create texture!");
    }

    screen_sprite_.setTexture(screen_texture_);

    core_.setScanlineCallback(std::bind(&DefaultView::scanlineCallback, this, std::placeholders::_1, std::placeholders::_2));
    core_.setVBlankCallback(std::bind(&DefaultView::vblankCallback, this));
}

std::string DefaultView::name()
{
    return "Debugger";
}

void DefaultView::render()
{
    const auto& draw_region = ImGui::GetContentRegionAvail();

    const auto width = draw_region.x;
    const auto height = draw_region.y;

    const auto col_width = width / 3;

    // Create Left Pane
    if (ImGui::BeginChild("left_pane", { col_width, height }))
    {
        drawExecutionControl();
        ImGui::Separator();
        drawRegisters();
        ImGui::Separator();
        drawDisassembly();

        ImGui::EndChild();
    }

    ImGui::SameLine();

    if (ImGui::BeginChild("display", { width - col_width, height }))
    {
        drawDisplay();
        ImGui::EndChild();
    }
}

void DefaultView::drawExecutionControl()
{
    if (debugger_.getMode() == DebuggerInterface::Mode::RUN)
    {
        if (ImGui::Button("Break"))
        {
            debugger_.setMode(DebuggerInterface::Mode::STEP);
        }

        debugger_.runFrame();
    }
    else
    {
        if (ImGui::Button("Run"))
        {
            debugger_.setMode(DebuggerInterface::Mode::RUN);
        }
        ImGui::SameLine();
        if (ImGui::Button("Step"))
        {
            debugger_.step();
        }
    }

    state_ = core_.getCPU()->getStatus();
}

void DefaultView::drawRegisters()
{
    ImGui::Columns(3, "registers", false);

    ImGui::Text("AF: %04X", state_.af);
    ImGui::Text("BC: %04X", state_.bc);
    ImGui::Text("DE: %04X", state_.de);
    ImGui::Text("HL: %04X", state_.hl);

    ImGui::NextColumn();

    ImGui::Text("SP: %04X", state_.sp);
    ImGui::Text("PC: %04X", state_.pc);

    ImGui::NextColumn();

    ImGui::Text("Z: %d", state_.flag_z);
    ImGui::Text("N: %d", state_.flag_n);
    ImGui::Text("H: %d", state_.flag_h);
    ImGui::Text("C: %d", state_.flag_c);

    ImGui::Columns(1);
}

void DefaultView::drawDisassembly()
{
    if (ImGui::BeginChild("disassembly_view"))
    {
        const auto& disassembly_data = debugger_.getDisassembly();
        const auto size = disassembly_data.size();

        ImGuiListClipper clipper(size);

        while (clipper.Step())
        {
            for (auto i = clipper.DisplayStart; i < clipper.DisplayEnd; ++i)
            {
                const auto& data = disassembly_data.at(i);

                const auto str = fmt::format("{:08X}|{:04X}| {}", data.memory_address, data.logical_address, data.disassem);
                ImGui::Selectable(str.c_str(), state_.pc == data.logical_address);
            }
        }

        ImGui::EndChild();
    }
}

void DefaultView::drawDisplay()
{
    const auto window_size = ImGui::GetContentRegionAvail();
    const auto texture_size = screen_texture_.getSize();
    const auto x_scale = window_size.x / texture_size.x;
    const auto y_scale = window_size.y / texture_size.y;

    screen_sprite_.setScale(x_scale, y_scale);

    ImGui::Image(screen_sprite_);
}

void DefaultView::scanlineCallback(const gb::GPU::Scanline& scanline, int line)
{
    // Buffer the scanline
    for (auto i = 0u; i < scanline.size(); ++i)
    {
        const auto& p = scanline[i];
        framebuffer_.write(i, line, sf::Color{ p.r, p.g, p.b, 255 });
    }
}

void DefaultView::vblankCallback()
{
    // A full frame is done
    // Update the screen texture
    screen_texture_.update(framebuffer_.data());
}
