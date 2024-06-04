#pragma once

#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <cmath>

#include <iostream>

class Processing
{
    float fade_speed;   // Brightness level per second
    float blur_speed;   // Blur strength

public:

    Processing(float fade_speed, float blur_speed)
    {
        this->fade_speed = fade_speed;
        this->blur_speed = blur_speed;
    }

    void fade_and_blur(Buffer<float>* buffer, float delta_time, unsigned int start, unsigned int stop) const
    {
        unsigned int buffer_size = buffer->get_buffer_size();
        unsigned int width = buffer->get_width();
        float* pixels = buffer->get_pixels();

        for (unsigned int i = start; i < stop; i += 4)
        {
            float original_value = pixels[i + 3];

            // Caclculate 3x3 average (blur)
            float blur_value = 0;

            for (int offset_x = -1; offset_x <= 1; offset_x++)
            {
                for (int offset_y = -1; offset_y <= 1; offset_y++)
                {
                    unsigned int sample_index = i + (offset_x * 4) + (offset_y * width * 4);
                    if (sample_index >= 0 && sample_index < buffer_size)
                        blur_value += pixels[sample_index + 3];
                }
            }

            blur_value /= 9;

            // Linear interpolation between original value and the blur value
            float new_value = original_value + (blur_value - original_value) * (blur_speed * delta_time);

            // Fade
            float fade_and_blur = new_value - fade_speed * delta_time;
            if (fade_and_blur < 0)
                fade_and_blur = 0;

            pixels[i + 3] = fade_and_blur;
        }
    }
};