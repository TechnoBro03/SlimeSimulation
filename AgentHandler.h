#pragma once

#include "AgentHandler.h"
#include "Agent.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Buffer.h"

#include <cmath>
//#include <stdlib.h>

class AgentHandler
{
private:
	Agent** agents;
	unsigned int num_agents;

public:
	AgentHandler(unsigned int num_agents, Buffer<float>* buffer)
	{
		this->num_agents = num_agents;
		agents = new Agent * [num_agents];

		for (unsigned int i = 0; i < num_agents; i++)
		{
			agents[i] = new Agent(buffer->get_width() / 2, buffer->get_height() / 2, Utilities::hash(i) / 683565275.417);
		}
	}

	void update_agents(Buffer<float>* buffer, float delta_time)
	{
		for (unsigned int i = 0; i < num_agents; i++)
		{
			agents[i]->update_rotation(buffer, delta_time);
			agents[i]->update_position(buffer, delta_time);
			agents[i]->draw(buffer);
		}
	}

	//static s::Uint sense(agent& a, float angle)
	//{
	//	float sensorAngle = a.rotation + angle;
	//	s::Uint sensorCenterX = a.x + cosf(sensorAngle) * sensorOffset;
	//	s::Uint sensorCenterY = a.y + sinf(sensorAngle) * sensorOffset;
	//	s::Uint sum = 0;
	//	for (int oX = -sensorSize; oX <= sensorSize; oX++)
	//	{
	//		for (int oY = -sensorSize; oY <= sensorSize; oY++)
	//		{
	//			s::Uint sampleX = sensorCenterX + oX;
	//			s::Uint sampleY = sensorCenterY + oY;
	//			if (sampleX >= 0 && sampleX < Renderer::width && sampleY >= 0 && sampleY < Renderer::height)
	//			{
	//				sum += Renderer::getPixel(index(sampleX, sampleY)).a;
	//				//sum += Renderer::getPixel(sampleX, sampleY).a;
	//			}
	//		}
	//	}
	//	return sum;
	//}

	//static void updateRotation(agent& a)
	//{
	//	s::Uint forward = sense(a, 0);
	//	s::Uint left = sense(a, sensorAngle);
	//	s::Uint right = sense(a, -sensorAngle);

	//	float random = (s::hash((s::Uint)(a.x*a.y))%1000)/1000.0f;
	//	if (forward > left && forward > right)
	//	{
	//		a.rotation += 0;
	//	}
	//	else if (forward < left && forward < right)
	//	{
	//		a.rotation += (random - 0.5) * 2 * turnSpeed; //*delta time
	//	}
	//	else if (right > left)
	//	{
	//		a.rotation -= random * turnSpeed;
	//	}
	//	else if (left > right)
	//	{
	//		a.rotation += random * turnSpeed;
	//	}

	//}

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