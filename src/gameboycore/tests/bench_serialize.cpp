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

static void BM_Serialize(benchmark::State& state)
{
    auto rom = loadRom("test_runner/test_roms/cpu_instrs/cpu_instrs.gb");

    GameboyCore core;
    core.loadROM(&rom[0], rom.size());

    for (auto _ : state)
        (void)core.serialize();
}

static void BM_Deserialize(benchmark::State& state)
{
    auto rom = loadRom("test_runner/test_roms/cpu_instrs/cpu_instrs.gb");

    GameboyCore core;
    core.loadROM(&rom[0], rom.size());

    const auto data = core.serialize();

    for (auto _ : state)
        (void)core.deserialize(data);
}

BENCHMARK(BM_Serialize);
BENCHMARK(BM_Deserialize);
