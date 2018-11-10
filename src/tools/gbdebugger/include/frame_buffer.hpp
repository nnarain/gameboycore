#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <vector>
#include <cstdint>

template<int WIDTH, int HEIGHT, int PIXEL_SIZE>
class Framebuffer
{
public:
    Framebuffer()
        : buffer_(WIDTH * HEIGHT * PIXEL_SIZE)
    {
    }

    template<typename PixelT>
    void write(int x, int y, PixelT pixel)
    {
        // calculate index into buffer
        auto idx = ((y * WIDTH) + x) * PIXEL_SIZE;
        // get pointer to data offset
        //auto ptr = &buffer_[idx];
        //*(ptr++) = pixel.r;
        //*(ptr++) = pixel.g;
        //*(ptr++) = pixel.b;
        //*(ptr++) = pixel.a;

        buffer_[idx + 0] = pixel.r;
        buffer_[idx + 1] = pixel.g;
        buffer_[idx + 2] = pixel.b;
        buffer_[idx + 3] = pixel.a;
    }

    const uint8_t* data() const
    {
        return &buffer_[0];
    }

    constexpr int width() const
    {
        return WIDTH;
    }

    constexpr int height() const
    {
        return HEIGHT;
    }

private:
    std::vector<uint8_t> buffer_;
};

#endif
