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
				if (ImGui::Checkbox("CPU debug", &cpu_debug_mode_))
				{
					core_.getCPU()->setDebugMode(cpu_debug_mode_);
				}

				if (ImGui::CollapsingHeader("Registers"))
				{
					auto state = core_.getCPU()->getStatus();

					ImGui::Text("PC: %04X, SP: %04X", state.pc, state.sp);
					ImGui::Text("A: %02X, BC: %04X, DE: %04X, HL: %04X", state.a, state.bc, state.de, state.hl);

					bool z = state.f & gb::CPU::Flags::Z;
					bool n = state.f & gb::CPU::Flags::N;
					bool h = state.f & gb::CPU::Flags::H;
					bool c = state.f & gb::CPU::Flags::C;

					ImGui::Text("Flags: Z N H C");
					ImGui::Text("       %d %d %d %d", z, n, h, c);
				}
			}

			if (ImGui::CollapsingHeader("Memory"))
			{

			}

			if (ImGui::CollapsingHeader("Graphics"))
			{
				if (ImGui::CollapsingHeader("Default Palette"))
				{

				}
			}

			if (ImGui::CollapsingHeader("Audio"))
			{

			}

			ImGui::End();
		}
	}

private:
	gb::GameboyCore& core_;
	bool cpu_debug_mode_;
};

#endif
