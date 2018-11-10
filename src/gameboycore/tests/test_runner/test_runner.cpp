#include <gameboycore/gameboycore.h>
#include <gameboycore/link_cable.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace gb;

namespace
{
    /**
        This class is used to analyize the output stream from the test ROM and determine is the program should exit
    */
    class ExitConditionStateMachine
    {
    public:
        ExitConditionStateMachine(const std::vector<std::string>& exit_strings)
            : exit_strings_{exit_strings}
            , current_sequence_{}
            , should_exit_{false}
        {
        }

        void update(char c)
        {
            // Append the new character to the existing sequence 
            current_sequence_ += c;
            // A counter to check failed sequence matches
            std::size_t failed_match_count = 0;

            // Check if the current sequence exists in any of the exit strings
            for (const auto& exit_string : exit_strings_)
            {
                // Search for the current sequence in this exit string
                auto it = std::search(
                    std::begin(exit_string), std::end(exit_string),
                    std::begin(current_sequence_), std::end(current_sequence_)
                );

                if (it != std::end(exit_string))
                {
                    // The sequence exists in the exit string
                    // Are they the same?
                    if (current_sequence_ == exit_string)
                    {
                        // the current sequence is an exit string, we should exit now
                        should_exit_ = true;
                        break;
                    }
                }
                else
                {
                    // The current sequence was not in this exit string
                    failed_match_count++;
                }
            }

            // Check if the current sequence was contained in any of the exit strings.
            if (failed_match_count == exit_strings_.size())
            {
                // No partial matches, clear the sequence.
                current_sequence_.clear();
            }
        }

        operator bool() const
        {
            return should_exit_;
        }
    private:
        // A list of string we should exit on
        std::vector<std::string> exit_strings_;
        // The currently best matching sequence string
        std::string current_sequence_;
        // Whether the exit condition has been met
        bool should_exit_;
    };

    std::vector<uint8_t> loadRom(const std::string& rom_path)
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
}

int main(int argc, char *argv[])
{
    /**
        This program is intended to run gameboy emulator test ROMs.
        It has a single argument which is the file to run.
        Test ROMs output to the serial port so we will use the link port API to print test results to the console
    */

    if (argc < 2)
    {
        std::cout << "Usage: test_runner rom/to/run" << std::endl;
        return 1;
    }

    // File path of the ROM to run
    std::string filepath{ argv[1] };

    // Load ROM data
    std::vector<uint8_t> data;

    try
    {
        data = loadRom(filepath);
    }
    catch (std::runtime_error& e)
    {
        std::cout << "Failed to load ROM file: " << e.what() << std::endl;
        return 1;
    }

    // Create a core and load the ROM data
    GameboyCore core;
    core.loadROM(&data[0], data.size());
    data.clear();

    // Create an exit condition state machine to track whether the test is done
    ExitConditionStateMachine exit_condition{ { "Fail", "fail", "Pass", "pass" } };

    // Setup link cable
    // This will be used to read output from the test ROMs
    LinkCable cable;
    // This callback fires when the core is ready to transfer a byte
    core.getLink()->setReadyCallback([&cable](uint8_t byte, Link::Mode mode) {
        // Signal core is ready for transfer
        cable.link1ReadyCallback(byte, mode);
        // Since there is no other core, we signal that the second link is ready as well
        // The serial transfer is master-slave system, the link modes must be opposite states
        cable.link2ReadyCallback(0xFF, (mode == Link::Mode::EXTERNAL) ? Link::Mode::INTERNAL : Link::Mode::EXTERNAL);
    });

    cable.setLink2RecieveCallback([&exit_condition](uint8_t byte) {
        // Sucessfully recieved a byte from the gameboy
        char c = (char)byte;
        std::cout << c;
        exit_condition.update(c);
    });

    // loop while we have not reached the exit condition
    while (!exit_condition)
    {
        core.update(1024);
    }

    // Print some padding characters
    std::cout << "\n\n";
    
    return 0;
}
