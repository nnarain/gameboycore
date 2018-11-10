#include "audio_stream.hpp"

#include <functional>

AudioStream::AudioStream()
    : running_{false}
{

}

void AudioStream::initialize(gb::GameboyCore& core)
{
    core.getAPU()->setAudioSampleCallback(std::bind(&AudioStream::audioSampleCallback, this, std::placeholders::_1, std::placeholders::_2));
}

void AudioStream::start()
{
    running_ = true;
    audio_thread_ = std::thread(std::bind(&AudioStream::playAudio, this));
}

void AudioStream::stop()
{
    sound_.stop();
    running_ = false;
    audio_thread_.join();
}

void AudioStream::playAudio()
{
    while (running_)
    {
        // Wait for sound to stop playing
        while (sound_.getStatus() == sf::Sound::Status::Playing)
        {
            sf::sleep(sf::milliseconds(5));
        }

        // load at the the minimum number of samples
        if (samples_.size() > MIN_SAMPLES)
        {
            buffer_.loadFromSamples(&samples_[0], samples_.size(), gb::APU::CHANNEL_COUNT, gb::APU::SAMPLE_RATE);
            sound_.setBuffer(buffer_);

            samples_.clear();

            sound_.play();
        }
    }
}

void AudioStream::audioSampleCallback(int16_t left, int16_t right)
{
    samples_.push_back(left);
    samples_.push_back(right);
}