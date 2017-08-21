#ifndef GAMEBOY_AUDIO_H
#define GAMEBOY_AUDIO_H

#include <SFML/Audio.hpp>

#include <gameboycore/apu.h>

#include <array>
#include <vector>
#include <thread>

/**
	Play Audio from gameboy core
*/
class Audio
{
	static constexpr unsigned int MIN_SAMPLES = 4096;

public:
	Audio() : 
		running_(false)
	{
	}

	~Audio()
	{
	}

	void start()
	{
		running_ = true;
		play_thread_ = std::thread(std::bind(&Audio::playAudio, this));
	}

	void stop()
	{
		sound_.stop();
		running_ = false;
		play_thread_.join();
	}

	void apuCallback(int16_t left, int16_t right)
	{
		samples_.push_back(left);
		samples_.push_back(right);
	}

private:

	void playAudio()
	{
		while (running_)
		{
			// wait for sound to stop playing
			while (sound_.getStatus() == sf::Sound::Status::Playing)
			{
				sf::sleep(sf::milliseconds(10));
			}

			// load at least the minimum number of samples
			if (samples_.size() >= MIN_SAMPLES)
			{
				buffer_.loadFromSamples(&samples_[0], samples_.size(), gb::APU::CHANNEL_COUNT, gb::APU::SAMPLE_RATE);
				sound_.setBuffer(buffer_);

				samples_.clear();

				sound_.play();
			}
		}
	}

	sf::Sound sound_;
	sf::SoundBuffer buffer_;
	std::thread play_thread_;
	bool running_;

	std::vector<sf::Int16> samples_;
};

#endif // GAMEBOY_AUDIO_H
