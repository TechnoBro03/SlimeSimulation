#pragma once

#include <SFML/Graphics.hpp>
#include "Renderer.h"
#include <cmath>

#include <iostream>

class Processing
{
    // Are these needed? different names for sure
    float fade_speed;   // Brightness level per second
    float blur_speed;   // 

public:

    Processing(float fade_speed, float blur_speed)
    {
        this->fade_speed = fade_speed;
        this->blur_speed = blur_speed;
    }

    void fade_and_blur(Buffer<float>* buffer, float delta_time)
    {
        unsigned int buffer_size = buffer->get_buffer_size();
        unsigned int width = buffer->get_width();
        float* pixels = buffer->get_pixels();

        for (unsigned int i = 0; i < buffer_size; i += 4)
        {
            float original_value = pixels[i + 3];

            // Caclculate 9x9 average for bluring
            float average_value = 0;

            for (int offset_x = -1; offset_x <= 1; offset_x++)
            {
                for (int offset_y = -1; offset_y <= 1; offset_y++)
                {
                    unsigned int sample_index = i + (offset_x * 4) + (offset_y * width * 4);
                    if (sample_index >= 0 && sample_index < buffer_size)
                        average_value += pixels[sample_index + 3];
                }
            }

            average_value /= 9;

            // Linear interpolation
            float blur_value = original_value + (average_value - original_value) * (blur_speed * delta_time);

            // Fade
            float fade_and_blur = blur_value - fade_speed * delta_time;
            if (fade_and_blur < 0)
                fade_and_blur = 0;

            pixels[i + 3] = fade_and_blur;
        }
    }

  //  // Start/Stop added for multithreading
  //  static void process(s::Uint start, s::Uint stop)
  //  {
  //      for (s::Uint i = start; i < stop; i += 4)
  //      {
  //          sf::Uint8 sum = 0;
  //          int x = i % Renderer::width;
  //          int y = i / Renderer::width;

  //          for (int oX = -1; oX < 2; oX++)
  //          {
  //              for (int oY = -1; oY < 2; oY++)
  //              {
  //                  int sampleX = x + oX;
  //                  int sampleY = y + oY;
  //                  if (sampleX >= 0 && sampleX < Renderer::width && sampleY >= 0 && sampleY < Renderer::height)
  //                  {
  //                      sum += Renderer::getPixel(index(sampleX, sampleY)).a;
  //                  }
  //              }
  //          }
  //          // Diffusion does not work... at all really. Should look like video, does not.
  //          sf::Color original = Renderer::getPixel(i);
  //          sf::Uint8 avg = sum / 9;

  //          sf::Uint8 diffuse = original.a * (1 - diffuseSpeed) + avg * diffuseSpeed;
  //          sf::Uint8 diffuse = original.a *(.9) + avg * 0.01;
  //          sf::Uint8 diffuseAndEvaporate = fmax(0, diffuse - evaporateSpeed); /// * delta
  //          original.a = diffuseAndEvaporate;
  //          Renderer::setPixel(i, original, true);


  //          sf::Color orig = Renderer::getPixel(i);
  //          original.a = original.a - evaporateSpeed;
  //          Renderer::setPixel(i, original);
  //      }
  //      for(s::Uint i = start; i < stop; i++)
		//{
  //          s::Uint sum = 0;
  //          s::Uint sampleX = i % Renderer::width;
  //          s::Uint sampleY = i / Renderer::width;
  //          for(int oX = -1; oX < 2; oX++)
  //          {
  //              for(int oY = -1; oY < 2; oY++)
  //              {
  //                  sampleX += oX;
  //                  sampleY += oY;
  //                  if (sampleX >= 0 && sampleX < Renderer::width && sampleY >= 0 && sampleY < Renderer::height)
  //                  {
  //                      sum += Renderer::getPixel(sampleX, sampleY).a;
  //                  }
  //              }
  //          }
  //          sf::Color original = Renderer::getPixel(i);

  //          float avg = sum/9;
  //          float diffuse = s::lerp(original.a, avg, diffuseSpeed); /// * delta
  //          sf::Uint8 diffuseAndEvaporate = fmax(0, diffuse - evaporateSpeed); /// * delta
  //          
  //          original.a = diffuseAndEvaporate;
  //          Renderer::setPixel(i, original);
  //      }
  //  }
};