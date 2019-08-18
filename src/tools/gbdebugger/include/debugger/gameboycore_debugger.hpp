#pragma once

#include "debugger/debugger_interface.hpp"
#include "debugger/disassembly_generator.hpp"

#include <gameboycore/gameboycore.h>

#include <string>
#include <map>
#include <thread>
#include <condition_variable>
#include <queue>
#include <tuple>

class GameboyCoreDebugger : public DebuggerInterface
{
public:
    /**
     * @param core A GameboyCore instace to manage
    */
    GameboyCoreDebugger(gb::GameboyCore& core);
    ~GameboyCoreDebugger();

    virtual void step() override;
    virtual void runFrame() override;
    
    virtual void setMode(Mode mode) override;

    virtual const DebuggerInterface::DisassemblyStorage& getDisassembly() override;

private:
    void disassemblyCallback(const DebuggerInterface::DisassemblyData& data);
    
    gb::GameboyCore& core_;

    DisassemblyGenerator disasm_generator_;
    DebuggerInterface::DisassemblyStorage disassembly_;
};