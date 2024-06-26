#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

template <typename T>
class Buffer
{
private:
	unsigned int width, height, buffer_size;
    T* pixels;

public:
    Buffer(unsigned int width, unsigned int height)
    {
        this->width = width;
        this->height = height;

        // 4 bytes per pixel, RGBA
        buffer_size = width * height * 4;

        pixels = new T[buffer_size];

        // Set all elements to 0
        std::fill(pixels, pixels + buffer_size, 0);
    }

    ~Buffer()
    {
        delete[] pixels;
    }

    unsigned int get_buffer_size() const
    {
        return buffer_size;
    }
    unsigned int get_width() const
    {
        return width;
    }
    unsigned int get_height() const
    {
        return height;
    }

    // Copies the pixels of one buffer into another.
    template <typename S, typename D>
    static void copy_pixels(Buffer<S>* source, Buffer<D>* destination)
    {
        std::copy(source->get_pixels(), source->get_pixels() + source->get_buffer_size(), destination->get_pixels());
    }

    T* get_pixels() const
    {
        return pixels;
    }

    void set_pixel(unsigned int x, unsigned int y, sf::Color color)
    {
        unsigned int i = (y * width + x) * 4;
        pixels[i] = color.r;
        pixels[i + 1] = color.g;
        pixels[i + 2] = color.b;
        pixels[i + 3] = color.a;
    }
};