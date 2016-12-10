
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <stdexcept>

#include <gameboycore/gameboycore.h>

#include "window.h"

#include "version.h"

using namespace gb;

class GameboyThread
{
public:

	GameboyThread(gb::GameboyCore& core) : core_(core)
	{
		running_ = true;
		thread_ = std::thread(std::bind(&GameboyThread::run, this));
	}

	void run()
	{
		while (running_)
		{
			core_.update(512);

			std::this_thread::sleep_for(std::chrono::milliseconds(5));
		}

		std::cout << "Thread Exiting" << std::endl;
	}

	~GameboyThread()
	{
		running_ = false;
		thread_.join();
	}

private:
	gb::GameboyCore& core_;

	std::thread thread_;
	bool running_;
};

class LinkCable
{
public:
	using RecieveCallback = std::function<void(uint8_t)>;

private:
	//! Contains link ready status, byte ti transfer and clocking mode
	struct LinkData
	{
		LinkData() :
			mode(Link::Mode::EXTERNAL),
			byte(0),
			ready(false)
		{
		}

		Link::Mode mode;
		uint8_t    byte;
		bool       ready;
	};

public:

	LinkCable()
	{
	}

	~LinkCable()
	{
	}

	void update()
	{
		if (link_data1_.ready && link_data2_.ready)
		{
			// both links indicate they are ready to transfer

			if (link_data1_.mode != link_data2_.mode)
			{
				transfer();
			}
		}
		else
		{
			// only one link is ready to tranfer, or neither are

			
			if (link_data1_.ready)
			{
				if (link_data1_.mode == Link::Mode::INTERNAL)
				{
					// if this link is the master device, supply it with a $FF
					link_data2_.byte = 0xFF;
					transfer();
				}
			}

			if (link_data2_.ready)
			{
				if (link_data2_.mode == Link::Mode::INTERNAL)
				{
					link_data1_.byte = 0xFF;
					transfer();
				}
			}
			
		}
	}

	void link1ReadyCallback(uint8_t byte, Link::Mode mode)
	{
		link_data1_.byte = byte;
		link_data1_.mode = mode;
		link_data1_.ready = true;
	}

	void link2ReadyCallback(uint8_t byte, Link::Mode mode)
	{
		link_data2_.byte = byte;
		link_data2_.mode = mode;
		link_data2_.ready = true;
	}

	void setLink1RecieveCallback(const RecieveCallback& callback)
	{
		recieve1_ = callback;
	}

	void setLink2RecieveCallback(const RecieveCallback& callback)
	{
		recieve2_ = callback;
	}

private:

	void transfer()
	{
		if(recieve1_)
			recieve1_(link_data2_.byte);
		
		if(recieve2_)
			recieve2_(link_data1_.byte);

		link_data1_.ready = false;
		link_data2_.ready = false;
	}

private:
	RecieveCallback recieve1_;
	RecieveCallback recieve2_;

	LinkData link_data1_;
	LinkData link_data2_;
};

static bool loadGB(GameboyCore& gameboy, const std::string& filename);
static std::vector<uint8_t> loadFile(const std::string& file);
static void saveRam(const std::string& file_name, const std::vector<uint8_t>& battery_ram);
static std::string saveFileName(const std::string& rom_filename);

int main(int argc, char * argv[])
{

	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <romfile>" << std::endl;
		return 1;
	}

	if (std::string(argv[1]) == "-v")
	{
		std::cout << version::get() << std::endl;
	}

	std::string filename(argv[1]);

	GameboyCore gameboy1;
	GameboyCore gameboy2;

	if (
		loadGB(gameboy1, filename) && 
		loadGB(gameboy2, filename)
		)
	{
		try
		{
			// setup render window
			std::string title = "Example " + version::get();

			Window window1(gameboy1, title + ": Window 1");
			window1.start();

			Window window2(gameboy2, title);
			window2.start();

			gameboy1.setDebugMode(false);
			gameboy2.setDebugMode(false);

			// setup link cable
			LinkCable cable;
			gameboy1.getLink()->setReadyCallback(std::bind(&LinkCable::link1ReadyCallback, &cable, std::placeholders::_1, std::placeholders::_2));
			gameboy2.getLink()->setReadyCallback(std::bind(&LinkCable::link2ReadyCallback, &cable, std::placeholders::_1, std::placeholders::_2));

			cable.setLink1RecieveCallback([&](uint8_t byte) {
				gameboy1.getLink()->recieve(byte);
			});
			cable.setLink2RecieveCallback([&](uint8_t byte) {
				gameboy2.getLink()->recieve(byte);
			});

			GameboyThread core_thread1(gameboy1);
			GameboyThread core_thread2(gameboy2);

			while (window1.isOpen())
			{
				cable.update();

				window1.update();
				window2.update();
			}
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}

		// Exiting save battery RAM

		// get battery ram from memory
		std::vector<uint8_t> battery_ram = gameboy1.getMMU()->getBatteryRam();

		saveRam(saveFileName(filename), battery_ram);
	}
	else
	{
		std::cout << "-- Unable to load rom file: " << argv[1] << std::endl;
	}

	return 0;
}

bool loadGB(GameboyCore& gameboy, const std::string& filename)
{
	std::vector<uint8_t> rom = loadFile(filename);
	std::vector<uint8_t> ram = loadFile(saveFileName(filename));

	if (rom.size() > 0)
	{
		gameboy.loadROM(&rom[0], rom.size());

		if (ram.size() > 0)
		{
			gameboy.getMMU()->setBatteryRam(ram);
		}

		return true;
	}

	return false;
}

std::vector<uint8_t> loadFile(const std::string& file_name)
{
	std::vector<uint8_t> data;

	std::ifstream file(file_name, std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		auto length = file.tellg();
		data.resize(length);

		file.seekg(0, std::ios::beg);
		file.read((char*)&data[0], length);
	}

	return data;
}

void saveRam(const std::string& file_name, const std::vector<uint8_t>& battery_ram)
{
	std::ofstream file(file_name, std::ios::binary);
	file.write((char*)&battery_ram[0], battery_ram.size());
}

std::string saveFileName(const std::string& rom_filename)
{
	return rom_filename.substr(0, rom_filename.rfind('.')) + ".sav";
}