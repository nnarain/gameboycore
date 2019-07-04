#pragma once

#include <string>
#include <vector>

class DebuggerInterface
{
public:
    enum class Mode
    {
        RUN,
        STEP
    };

    struct DisassemblyData
    {
        uint16_t logical_address;
        size_t memory_address;
        std::string disassem;
        std::string annotation;
    };

    using DisassemblyStorage = std::vector<DebuggerInterface::DisassemblyData>;

    DebuggerInterface()
        : mode_{Mode::RUN}
    {
    }

    virtual ~DebuggerInterface() = default;

    virtual void step() = 0;
    virtual void runFrame() = 0;

    virtual const DisassemblyStorage& getDisassembly() = 0;

    virtual void setMode(Mode mode)
    {
        mode_ = mode;
    }

    Mode getMode() const
    {
        return mode_;
    }

protected:
    Mode mode_;
};
