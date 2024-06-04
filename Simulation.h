#pragma once

#include "AgentHandler.h"
#include "Agent.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Buffer.h"
#include "Processing.h"
#include "FrameRate.h"
#include "Settings.h"
#include <thread>


class Simulation
{
private:
	Settings* settings;
public:
	Simulation(Settings* settings)
	{
		this->settings = settings;
	}
	void run()
	{
		Renderer renderer(settings->get_width(), settings->get_height(), settings->get_frame_rate_limit());
		Buffer<unsigned char> pixel_buffer(settings->get_width(), settings->get_height());
		Buffer<float> float_buffer(settings->get_width(), settings->get_height());

		AgentHandler agent_handler(settings->get_width(), settings->get_height(), settings->get_num_agents(), settings->get_speed(), settings->get_turn_speed(),
			settings->get_sensor_offset(), settings->get_sensor_angle(), settings->get_sensor_size());
		Processing processing(settings->get_fade_speed(), settings->get_blur_speed());

		FrameRate frame_rate(settings->get_average_frame_rate_window());
		sf::Clock clock;

		std::thread* threads;
		unsigned int num_threads = settings->get_num_threads();
		threads = new std::thread[num_threads];

		while (renderer.is_open())
		{

			// Get delta time
			float delta_time = clock.restart().asSeconds();

			// Track average frame rate
			frame_rate.add_frame_time(delta_time);

			// Update simulation
			// 
			// Update agents
			for (unsigned int i = 0; i < num_threads; i++)
			{
				// Create starting and stopping points for thread
				unsigned int start = settings->get_num_agents() * ((double)i / num_threads);
				unsigned int stop = settings->get_num_agents() * ((double)(i + 1) / num_threads);

				// Start each thread
				threads[i] = std::thread([&agent_handler, &float_buffer, delta_time, start, stop]()
					{
					agent_handler.update_agents(&float_buffer, delta_time, start, stop);
					});
			}

			// Join all threads
			for (int i = 0; i < num_threads; i++)
			{
				if (threads[i].joinable())
					threads[i].join();
			}

			// Update pixels
			for (int i = 0; i < num_threads; i++)
			{
				// Create starting and stopping points for thread
				unsigned int start = (float_buffer.get_buffer_size() / 4) * ((double)i / num_threads);
				unsigned int stop = (float_buffer.get_buffer_size() / 4) * ((double)(i + 1) / num_threads);

				// Start each thread
				threads[i] = std::thread([&processing, &float_buffer, delta_time, start, stop]()
					{
					processing.fade_and_blur(&float_buffer, delta_time, start * 4, stop * 4);
					});
			}
			// Join all threads
			for (int i = 0; i < num_threads; i++)
			{
				if (threads[i].joinable())
					threads[i].join();
			}

			// Copy float_buffer into pixel_buffer (textures do not support floats)
			Buffer<unsigned char>::copy_pixels(&float_buffer, &pixel_buffer);

			// Draw to the screen
			renderer.draw(&pixel_buffer, frame_rate.get_average_frame_rate());

			// Handle events
			renderer.handle_events();
		}

		delete[] threads;
	}
};