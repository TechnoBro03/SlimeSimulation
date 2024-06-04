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
	enum SpawnPattern
	{
		random = 0, center_out, circle_out, circle_in, ring
	};
	AgentHandler(unsigned int width, unsigned int height, unsigned int num_agents, SpawnPattern sp, float speed, float turn_speed, unsigned int sensor_offset, float sensor_angle,unsigned int sensor_size)
	{
		this->num_agents = num_agents;
		agents = new Agent * [num_agents];

		float x = 0, y = 0, rotation = 0, r, angle, radius, inner, outer;
		const float target_x = width / 2, target_y = height / 2;

		for (unsigned int i = 0; i < num_agents; i++)
		{
			switch (sp)
			{
			// All random
			case SpawnPattern::random:
				x = rand() / (float)RAND_MAX * width;
				y = rand() / (float)RAND_MAX * height;
				rotation = rand() / (RAND_MAX * 0.5f) * Utilities::PI;
				break;

			// Spawn in the center of screen facing out
			case SpawnPattern::center_out:
				x = target_x;
				y = target_y;
				rotation = rand() / (RAND_MAX * 0.5f) * Utilities::PI;
				break;

			// Spawn in a circle facing out
			case SpawnPattern::circle_out:
				radius = 300;
				angle = rand() / (RAND_MAX * 0.5f) * Utilities::PI;
				r = radius * std::sqrt((float)rand() / RAND_MAX);
				x = r * std::cos(angle) + target_x;
				y = r * std::sin(angle) + target_y;
				rotation = std::atan2(y - target_y, x - target_x);
				break;
				
			// Spawn in a circle facing in
			case SpawnPattern::circle_in:
				radius = 300;
				angle = rand() / (RAND_MAX * 0.5f) * Utilities::PI;
				r = radius * std::sqrt((float)rand() / RAND_MAX);
				x = r * std::cos(angle) + target_x;
				y = r * std::sin(angle) + target_y;
				rotation = std::atan2(target_y - y, target_x - x);
				break;
			
			// Spawn in a ring facing tangentially
			case SpawnPattern::ring:
				inner = 200;  outer = 400;
				angle = rand() / (RAND_MAX * 0.5f) * Utilities::PI;
				r = std::sqrt((float)rand() / RAND_MAX * (outer * outer - inner * inner) + inner * inner);
				x = target_x + r * std::cos(angle);
				y = target_y + r * std::sin(angle);
				rotation = std::atan2(y - target_y, x - target_x) + Utilities::PI / 2;
				break;
			default:
				break;
			}

			agents[i] = new Agent(x, y, rotation, speed, turn_speed, sensor_offset, sensor_angle, sensor_size);
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
		for (unsigned int i = 0; i < num_agents; i++)
		{
			delete agents[i];
		}
		delete[] agents;
	}
};