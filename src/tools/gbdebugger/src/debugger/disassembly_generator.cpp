#include "debugger/disassembly_generator.hpp"

DisassemblyGenerator::DisassemblyGenerator(gb::GameboyCore& core)
    : disassembly_running_{false}
{
    auto& mmu = core.getMMU();
    logical_to_memory_ = std::bind(&gb::MMU::resolveAddress, mmu.get(), std::placeholders::_1);

    core.setInstructionCallback(std::bind(&DisassemblyGenerator::instructionCallback, this, std::placeholders::_1, std::placeholders::_2));

    disassembly_running_ = true;
    disassemble_thread_ = std::thread(&DisassemblyGenerator::disassemblyThread, this);
}

DisassemblyGenerator::~DisassemblyGenerator()
{
    disassembly_running_ = false;
    cv.notify_one();

    disassemble_thread_.join();
}

void DisassemblyGenerator::instructionCallback(const gb::Instruction& instruction, const uint16_t addr)
{
    const auto memory_address = logical_to_memory_(addr);
    const auto data = std::tie(addr, memory_address, instruction);

    {
        LockGuard lock{ queue_mutex_ };

        if (instruction_cache_.find(memory_address) == instruction_cache_.end())
        {
            disassembly_queue_.push(data);
            instruction_cache_.insert(memory_address);
        }

        cv.notify_one();
    }
}

void DisassemblyGenerator::disassemblyThread()
{
    while (disassembly_running_)
    {
        UniqueLock lock{ queue_mutex_ };
        cv.wait(lock, [&]() {return !disassembly_queue_.empty(); });

        while (!disassembly_queue_.empty())
        {
            const auto& data = disassembly_queue_.front();
            disassembly_queue_.pop();

            DebuggerInterface::DisassemblyData disasm_data;
            disasm_data.logical_address = std::get<0>(data);
            disasm_data.memory_address = std::get<1>(data);
            disasm_data.disassem = gb::disassemble(std::get<2>(data));

            callback_(disasm_data);
        }
    }
}

void DisassemblyGenerator::setDisassemblyCallback(std::function<void(const DebuggerInterface::DisassemblyData&)> fn)
{
    callback_ = fn;
}