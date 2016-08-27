#include <cxxtest/TestSuite.h>

#include <gameboy/gameboy.h>

#include <vector>
#include <string>
#include <fstream>

bool loadGB(const std::string& file_name, std::vector<uint8_t>& buffer);

class LoadInstructionsTestSuite : public CxxTest::TestSuite
{
public:

	void testLoadImmediate()
	{
		TS_ASSERT(true == true);
	}

private:
};

bool loadGB(const std::string& file_name, std::vector<uint8_t>& buffer)
{
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if(file.is_open())
    {
        size_t length = (size_t)file.tellg();
        buffer.resize(length);

        file.seekg(0, std::ios::beg);
        file.read((char*)&buffer[0], length);

        return true;
    }
    else
    {
        return false;
    }
}