//#include <SFML/Graphics.hpp>

//#include "Simulation.h"
#include "AgentHandler.h"
#include "Agent.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Buffer.h"
#include "Processing.h"
#include "FrameRate.h"
#include <thread>

int main()
{

	// Add colors
	// Add pausing?
	// tweak params for agents

	Renderer renderer(720, 480, 120);
	Buffer<unsigned char> pixel_buffer(720, 480);
	Buffer<float> float_buffer(720, 480);

	AgentHandler agent_handler(100000);
	Processing processing(500, 0);

	FrameRate frame_rate(100);
	sf::Clock clock;

	while (renderer.is_open())
	{
		// Get delta time
		float delta_time = clock.restart().asSeconds();

		// Track average frame rate
		frame_rate.add_frame_time(delta_time);

		// Update simulation
		agent_handler.update_agents(&float_buffer, delta_time);
		processing.fade_and_blur(&float_buffer, delta_time);

		//// Create threads to run the functions concurrently
		//std::thread thread1(&AgentHandler::update_agents, &agent_handler, &float_buffer, delta_time);
		//std::thread thread2(&Processing::fade_and_blur, &processing, &float_buffer, delta_time);

		//// Wait for both threads to finish
		//thread1.join();
		//thread2.join();

		// Copy float_buffer into pixel_buffer to be drawn
		Buffer<unsigned char>::copy_buffer(&float_buffer, &pixel_buffer);
		// Draw to the screen
		renderer.draw(&pixel_buffer, frame_rate.get_average_frame_rate());

		// Handle events
		renderer.handle_events();
	}

	return 0;
}