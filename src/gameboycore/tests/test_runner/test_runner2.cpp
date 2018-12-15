#include <gameboycore/gameboycore.h>

#include <array>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace gb;

namespace
{
    constexpr uint8_t STATUS_RUNNING_TEST = 0x80;

    using clock = std::chrono::steady_clock;
    using time_point = std::chrono::time_point<clock>;
    
    std::array<uint8_t, 3> getSignature(GameboyCore& core)
    {
        std::array<uint8_t, 3> sig;

        for (auto i = 0u; i < sig.size(); ++i)
        {
            sig[i] = core.readMemory(0xA001 + i);
        }

        return sig;
    }

    bool verifySignature(const std::array<uint8_t, 3>& sig) noexcept
    {
        return sig[0] == 0xDE && sig[1] == 0xB0 && sig[2] == 0x61;
    }

    bool isTestRom(GameboyCore& core)
    {
        return verifySignature(getSignature(core));
    }
    
    bool testTimeout(const time_point& start_time, const std::chrono::milliseconds& timeout)
    {
        auto end_time = clock::now();
        auto elasped = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        return elasped > timeout;
    }
    
    uint8_t getStatus(GameboyCore& core)
    {
        return core.readMemory(0xA000);
    }

    std::string getOutputString(GameboyCore& core)
    {
        std::stringstream output;
        auto addr = 0xA004;

        char c = -1;
        do
        {
            c = (char)core.readMemory(addr++);
            
            if (c != '\0')
            {
                output << c;
            }
        }
        while (c != '\0');

        return output.str();
    }

    std::string getOutputDifference(const std::string& old_output, const std::string& current_output)
    {
        std::string difference;

        // Check that the string are actually different
        if (current_output != old_output)
        {
            // Get the difference in the two strings
            const auto current_size = current_output.size();
            const auto old_size = old_output.size();
            const auto len_diff = current_size - old_size;

            difference = current_output.substr(old_output.size(), len_diff);
        }

        return difference;
    }
}

int main(int argc, char const *argv[])
{
    /**
        This program is intended to run gameboy emulator test ROMs.
        It has a single argument which is the file to run.
        Test ROMs output to memory starting at $A000

        $A000       -> Status, $80 for active test
        $A001-$A003 -> Signature, $DE,$B0,$61
        $A004       -> NULL terminated string with result code for each test
    */

    if (argc < 2)
    {
        std::cout << "Usage: ./" << argv[0] << " rom/to/run\n";
        return 1;
    }

    // File path to the ROM file
    std::string filepath{ argv[1] };

    // Create a core and load the ROM data
    GameboyCore core;

    try
    {
        core.open(filepath);
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "Failed to load ROM file: " << e.what() << "\n";
        return 1;
    }

    // Emulate a frame to give the test ROM a chance to load RAM with status values
    core.emulateFrame();

    // Verify we are running a valid test ROM
    if (!isTestRom(core))
    {
        std::cerr << "This is not a valid test ROM\n";
        return 1;
    }
    
    // Get the start time of the test
    // This is to time it out if it hangs
    const auto start_time = std::chrono::steady_clock::now();
    const auto timeout = std::chrono::milliseconds(2 * 60 * 100);

    // Current output string
    std::string current_output;

    while (!testTimeout(start_time, timeout))
    {
        core.emulateFrame();

        auto output = getOutputString(core);
        auto output_diff = getOutputDifference(current_output, output);
        current_output = output;

        std::cout << output_diff;

        auto status = getStatus(core);
        if (status != STATUS_RUNNING_TEST)
        {
            break;
        }
    }

    std::cout << "\n\n";

    return 0;
}
