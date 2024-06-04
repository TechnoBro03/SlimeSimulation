#pragma once

#include "AgentHandler.h"
#include "Agent.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Buffer.h"

#include <cmath>

class AgentHandler
{
private:
	Agent** agents;
	unsigned int num_agents;

public:
	AgentHandler(unsigned int width, unsigned int height, unsigned int num_agents, float speed, float turn_speed, unsigned int sensor_offset, float sensor_angle,unsigned int sensor_size)
	{
		this->num_agents = num_agents;
		agents = new Agent * [num_agents];

		for (unsigned int i = 0; i < num_agents; i++)
		{
			agents[i] = new Agent(width / 2, height / 2, Utilities::hash(i) / 683565275.417, speed, turn_speed, sensor_offset, sensor_angle, sensor_size);
		}
	}

	void update_agents(Buffer<float>* buffer, float delta_time, unsigned int start, unsigned int stop)
	{
		for (unsigned int i = start; i < stop; i++)
		{
			agents[i]->update_rotation(buffer, delta_time);
			agents[i]->update_position(buffer, delta_time);
			agents[i]->draw(buffer);
		}
	}

public:
	~AgentHandler()
	{
		// Change to delete all constructed objects
		for (unsigned int i = 0; i < num_agents; i++)
		{
			delete agents[i];
		}
		delete[] agents;
	}

	//// Start/stop points included for multithreading
	//static void updateAgents(s::Uint start, s::Uint stop)
	//{
	//	for(s::Uint i = start; i < stop; i++)
	//	{
	//		agent& a = agents[i];
	//		addTrail(a);
	//		updateRotation(a);
	//		updatePosition(a);
	//	}
	//}

	//static void randomStart()
	//{
	//	for (s::Uint i = 0; i < numAgents; i++)
	//	{
	//		agents[i].x = s::hash(i) % Renderer::width;
	//		agents[i].y = s::hash(i * i) % Renderer::height;
	//		agents[i].rotation = (s::hash(i) % 2141) / 214.1;
	//	}
	//}
};