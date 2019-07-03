#pragma once

#include <debugger/debugger_interface.hpp>

#include <gameboycore/gameboycore.h>

#include <string>
#include <functional>
#include <queue>
#include <set>
#include <thread>
#include <condition_variable>

class DisassemblyGenerator
{
public:
    using QueueData = std::tuple<uint16_t, int, gb::Instruction>;
    using LockGuard = std::lock_guard<std::mutex>;
    using UniqueLock = std::unique_lock<std::mutex>;

    DisassemblyGenerator(gb::GameboyCore& core);
    ~DisassemblyGenerator();

    void instructionCallback(const gb::Instruction& instruction, const uint16_t addr);

    void setDisassemblyCallback(std::function<void(const DebuggerInterface::DisassemblyData&)>);

private:
    void disassemblyThread();

    std::function<int(uint16_t)> logical_to_memory_;

    std::thread disassemble_thread_;
    bool disassembly_running_;

    std::queue<QueueData> disassembly_queue_;
    std::mutex queue_mutex_;
    std::condition_variable cv;

    std::set<int> instruction_cache_;

    std::function<void(const DebuggerInterface::DisassemblyData&)> callback_;
};
