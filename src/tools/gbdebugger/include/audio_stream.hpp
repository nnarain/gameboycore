#ifndef AUDIO_STREAM_H
#define AUDIO_STREAM_H

#include <SFML/Audio.hpp>

#include <gameboycore/gameboycore.h>

#include <thread>
#include <vector>

class AudioStream
{
    static constexpr unsigned int MIN_SAMPLES = 4096;

public:
    AudioStream();
    ~AudioStream() = default;

    void initialize(gb::GameboyCore& core);

    void start();
    void stop();

private:
    void audioSampleCallback(int16_t, int16_t);
    void playAudio();

    sf::Sound sound_;
    sf::SoundBuffer buffer_;
    std::thread audio_thread_;
    bool running_;

    std::vector<sf::Int16> samples_;
};

#endif