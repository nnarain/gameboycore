#include "debugger/gameboycore_debugger.hpp"

#include <functional>
#include <thread>

using namespace gb;

GameboyCoreDebugger::GameboyCoreDebugger(gb::GameboyCore& core)
    : core_{core}
    , disasm_generator_{core}
{
    disasm_generator_.setDisassemblyCallback(std::bind(&GameboyCoreDebugger::disassemblyCallback, this, std::placeholders::_1));

    core.setDebugMode(true);
}

GameboyCoreDebugger::~GameboyCoreDebugger()
{
}

void GameboyCoreDebugger::step()
{
    core_.update(1);
}

void GameboyCoreDebugger::runFrame()
{
    core_.emulateFrame();
}

const DebuggerInterface::DisassemblyStorage& GameboyCoreDebugger::getDisassembly()
{
    return disassembly_;
}

void GameboyCoreDebugger::disassemblyCallback(const DebuggerInterface::DisassemblyData& data)
{
    disassembly_.push_back(data);

    std::sort(std::begin(disassembly_), std::end(disassembly_),
        [](const auto& lhs, const auto& rhs) {return lhs.memory_address < rhs.memory_address; });
}

void GameboyCoreDebugger::setMode(Mode mode)
{
    DebuggerInterface::setMode(mode);
    core_.setDebugMode(mode == DebuggerInterface::Mode::STEP);
}
