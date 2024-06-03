#pragma once

#include <SFML/Graphics.hpp>

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

        buffer_size = width * height * 4;

        pixels = new T[buffer_size];

        // Set all elements to 0
        std::fill(pixels, pixels + buffer_size, 0);
    }

    ~Buffer()
    {
        delete[] pixels;
    }

    unsigned int get_buffer_size()
    {
        return buffer_size;
    }
    unsigned int get_width()
    {
        return width;
    }
    unsigned int get_height()
    {
        return height;
    }

    // Copies the pixels of one buffer into another.
    template <typename S, typename D>
    static void copy_pixels(Buffer<S>* source, Buffer<D>* destination)
    {
        std::copy(source->get_pixels(), source->get_pixels() + source->get_buffer_size(), destination->get_pixels());
    }

    T* get_pixels()
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

    //sf::Color get_pixel(unsigned int i)
    //{
    //    /*unsigned int i = (y * width + x) * 4;*/
    //    sf::Uint8 r, g, b, a;
    //    r = pixels[i];
    //    g = pixels[i + 1];
    //    b = pixels[i + 2];
    //    a = pixels[i + 3];
    //    return sf::Color(r, g, b, a);
    //}
};