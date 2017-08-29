#ifndef EMULATOR_DEBUG_WINDOW_H
#define EMULATOR_DEBUG_WINDOW_H

#include "imgui.h"
#include "gameboycore/gameboycore.h"

#include <iostream>

class DebugWindow
{
private:
	struct AudioBuffer
	{
		AudioBuffer() : buffer{0}, index(0)
		{
		}

		void update(uint8_t volume)
		{
			buffer[index] = volume;
			index = (index + 1) % buffer.size();
		}

		std::array<float, 100> buffer;
		int index;
	};

public:

	DebugWindow(gb::GameboyCore& core) :
		core_(core),
		cpu_debug_mode_(false),
		color0{ 1,1,1,1},
		color1{ 192.0f/255.0f,192.0f / 255.0f,192.0f / 255.0f,255 },
		color2{ 96.f/255.f,96.f / 255.f,96.f / 255.f,255 },
		color3{ 0,0,0,255 }
	{
		core_.getCPU()->setDisassemblyCallback(std::bind(&DebugWindow::disassemblyCallback, this, std::placeholders::_1));
	}

	~DebugWindow()
	{
	}

	void draw(unsigned int width, unsigned int height)
	{
		ImGui::SetNextWindowPos(ImVec2((float)width, (float)height));

		if (ImGui::Begin("DebugWindow"))
		{
			if (ImGui::CollapsingHeader("CPU"))
			{
				if (ImGui::CollapsingHeader("Status"))
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
					drawEditPalette();
				}
			}

			if (ImGui::CollapsingHeader("Audio"))
			{
				auto& apu = core_.getAPU();

				sound1_.update(apu->getSound1Volume());
				sound2_.update(apu->getSound2Volume());
				sound3_.update(apu->getSound3Volume());
				sound4_.update(apu->getSound4Volume());

				drawSoundChannel("Square 1", sound1_);
				drawSoundChannel("Square 2", sound2_);
				drawSoundChannel("Wave    ", sound3_);
				drawSoundChannel("Noise   ", sound4_);
			}

			ImGui::End();
		}
	}

private:
	void drawSoundChannel(const char * label, AudioBuffer& channel)
	{
		ImGui::PlotLines(label, &channel.buffer[0], channel.buffer.size(), 0, nullptr, 0, 15);
	}

	void drawEditPalette()
	{
		ImGui::ColorEdit4("Color 0", color0, false);
		ImGui::ColorEdit4("Color 1", color1, false);
		ImGui::ColorEdit4("Color 2", color2, false);
		ImGui::ColorEdit4("Color 3", color3, false);

		auto& gpu = core_.getGPU();

		setPaletteColor(gpu, color0, 0);
		setPaletteColor(gpu, color1, 1);
		setPaletteColor(gpu, color2, 2);
		setPaletteColor(gpu, color3, 3);
	}

	void setPaletteColor(gb::GPU::Ptr& gpu, float* color, int idx)
	{
		uint8_t r = (uint8_t)(color[0] * 255);
		uint8_t g = (uint8_t)(color[1] * 255);
		uint8_t b = (uint8_t)(color[2] * 255);

		gpu->setPaletteColor(r, g, b, idx);
	}

	void drawCpuStatus()
	{
		auto status = core_.getCPU()->getStatus();

		ImGui::Text("PC: %04X, SP: %04X", status.pc, status.sp);
		ImGui::Text("A: %02X, BC: %04X, DE: %04X, HL: %04X", status.a, status.bc, status.de, status.hl);

		bool z = (status.f & gb::CPU::Flags::Z) != 0;
		bool n = (status.f & gb::CPU::Flags::N) != 0;
		bool h = (status.f & gb::CPU::Flags::H) != 0;
		bool c = (status.f & gb::CPU::Flags::C) != 0;

		ImGui::Text("Flags: Z N H C");
		ImGui::Text("       %d %d %d %d", z, n, h, c);

		bool j = (status.enabled_interrupts & (1 << 4)) != 0;
		bool s = (status.enabled_interrupts & (1 << 3)) != 0;
		bool t = (status.enabled_interrupts & (1 << 2)) != 0;
		bool l = (status.enabled_interrupts & (1 << 1)) != 0;
		bool v = (status.enabled_interrupts & (1 << 0)) != 0;

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
	
	// CPU
	bool cpu_debug_mode_;
	ImGuiTextBuffer disassembly_buffer_;

	// Graphics
	float color0[4];
	float color1[4];
	float color2[4];
	float color3[4];

	// Audio
	AudioBuffer sound1_;
	AudioBuffer sound2_;
	AudioBuffer sound3_;
	AudioBuffer sound4_;
};

#endif
