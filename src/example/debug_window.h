#ifndef EMULATOR_DEBUG_WINDOW_H
#define EMULATOR_DEBUG_WINDOW_H

#include "imgui.h"
#include "gameboycore/gameboycore.h"

class DebugWindow
{
public:

	DebugWindow(gb::GameboyCore& core) :
		core_(core),
		cpu_debug_mode_(false)
	{
		core_.getCPU()->setDisassemblyCallback(std::bind(&DebugWindow::disassemblyCallback, this, std::placeholders::_1));
	}

	~DebugWindow()
	{
	}

	void draw(unsigned int width, unsigned int height)
	{
		ImGui::SetNextWindowPos(ImVec2(width, height));

		if (ImGui::Begin("DebugWindow"))
		{
			if (ImGui::CollapsingHeader("CPU"))
			{
				if (ImGui::CollapsingHeader("Registers"))
				{
					drawCpuStatus();
				}

				if (ImGui::CollapsingHeader("Disassembly"))
				{
					if (ImGui::Checkbox("Toggle Disassembly", &cpu_debug_mode_))
					{
						core_.getCPU()->setDebugMode(cpu_debug_mode_);
					}

					drawDisassembly();
				}
			}

			if (ImGui::CollapsingHeader("Graphics"))
			{
				if (ImGui::CollapsingHeader("Default Palette"))
				{

				}
			}

			ImGui::End();
		}
	}

private:
	void drawCpuStatus()
	{
		auto status = core_.getCPU()->getStatus();

		ImGui::Text("PC: %04X, SP: %04X", status.pc, status.sp);
		ImGui::Text("A: %02X, BC: %04X, DE: %04X, HL: %04X", status.a, status.bc, status.de, status.hl);

		bool z = status.f & gb::CPU::Flags::Z;
		bool n = status.f & gb::CPU::Flags::N;
		bool h = status.f & gb::CPU::Flags::H;
		bool c = status.f & gb::CPU::Flags::C;

		ImGui::Text("Flags: Z N H C");
		ImGui::Text("       %d %d %d %d", z, n, h, c);

		bool j = status.enabled_interrupts & (1 << 4);
		bool s = status.enabled_interrupts & (1 << 3);
		bool t = status.enabled_interrupts & (1 << 2);
		bool l = status.enabled_interrupts & (1 << 1);
		bool v = status.enabled_interrupts & (1 << 0);

		ImGui::Text("IME - J S T L V");
		ImGui::Text("  %d - %d %d %d %d %d", status.ime, j, s, t, l, v);
	}

	void drawDisassembly()
	{
		if (ImGui::BeginChild("scrolling", ImVec2(), false, ImGuiWindowFlags_HorizontalScrollbar))
		{
			ImGui::TextUnformatted(disassembly_buffer_.begin());
			ImGui::SetScrollHere(1.0f);

			ImGui::EndChild();
		}
	}

	void disassemblyCallback(const std::string& disassembly)
	{
		disassembly_buffer_.append("%s\n", disassembly.c_str());
	}

	gb::GameboyCore& core_;
	bool cpu_debug_mode_;

	ImGuiTextBuffer disassembly_buffer_;
};

#endif
