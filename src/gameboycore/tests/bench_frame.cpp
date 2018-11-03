#include <benchmark/benchmark.h>
#include <gameboycore/gameboycore.h>

#include <fstream>
#include <string>
#include <vector>

using namespace gb;

static std::vector<uint8_t> loadRom(const std::string& rom_path)
{
    std::vector<uint8_t> data;

    std::ifstream file{ rom_path, std::ios::binary | std::ios::ate };
    if (file.is_open())
    {
        auto length = file.tellg();
        data.resize((std::size_t)length);

        file.seekg(0, std::ios::beg);
        file.read((char*)&data[0], length);
    }
    else
    {
        throw std::runtime_error("Could not open file specified");
    }

    return data;
}

static void BM_EmulateFrame(benchmark::State& state)
{
    auto rom = loadRom("test_runner/test_roms/cpu_instrs/cpu_instrs.gb");

    GameboyCore core;
    core.loadROM(&rom[0], rom.size());

    for (auto _ : state)
        core.emulateFrame();
}

BENCHMARK(BM_EmulateFrame);
