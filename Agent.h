#pragma once

#include "AgentHandler.h"
#include "Agent.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Buffer.h"

class Agent
{
private:
	float x, y, rotation;
	float sensorOffset; // Distance from agent
	float sensorSize; // Radius of sensor
	float sensorAngle; // Angle in radians
	float speed; // Speed
	float turnSpeed; // Turn speed
	
public:
	Agent(float x, float y, float roation)
	{
		this->x = x; this->y = y; this->rotation = roation;
		sensorOffset = 10;
		sensorSize = 7;
		sensorAngle = .5;
		speed = 150; // Pixels per second
		turnSpeed = 1;
	}

	void draw(Buffer<float>* buffer)
	{
		buffer->set_pixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y), sf::Color::White);
	}

	void update_position(Buffer<float>* buffer, float delta_time)
	{
		// Moves based on speed & delta time
		x += cosf(rotation) * speed * delta_time;
		y += sinf(rotation) * speed * delta_time;

		// Fixes out of bounds
		// 
		// 
		//if (x < 0 || x >= width || y < 0 || y >= height)
		//{
		//	x = fmin(width - 1, fmax(0, x));
		//	y = fmin(height - 1, fmax(0, y));
		//	// Turns randomly
		//	rotation += (Utilities::hash((unsigned int)x * y * rotation) / 683565275.417);
		//}

		unsigned int width = buffer->get_width();
		unsigned int height = buffer->get_height();

		// Check for collision with the left or right boundary
		if (x < 0 || x >= width)
		{
			rotation = Utilities::PI - rotation; // Reflect the angle horizontally
			x = fmin(width - 1, fmax(0, x)); // Correct the position to be within bounds
		}

		// Check for collision with the top or bottom boundary
		if (y < 0 || y >= height)
		{
			rotation = -rotation; // Reflect the angle vertically
			y = fmin(height - 1, fmax(0, y)); // Correct the position to be within bounds
		}
	}
};