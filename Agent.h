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
	float sensor_offset; // Distance from agent
	int sensor_size; // Side length of square sensor
	float sensor_angle; // Angle in radians
	float speed; // Speed
	float turn_speed; // Turn speed
	
public:
	Agent(float x, float y, float roation, float speed, float turn_speed, unsigned int sensor_offset, float sensor_angle, unsigned int sensor_size)
	{
		this->x = x; this->y = y; this->rotation = roation;
		this->sensor_offset = sensor_offset;
		this->sensor_size = sensor_size;
		this->sensor_angle = sensor_angle;
		this->speed = speed;
		this->turn_speed = turn_speed;
	}

	void draw(Buffer<float>* buffer)
	{
		buffer->set_pixel((unsigned int)x, (unsigned int)y, sf::Color::Magenta);
	}

	void update_rotation(Buffer<float>* buffer, float delta_time)
	{
		float forward_weight = sense(0, buffer);
		float left_weight = sense(-sensor_angle, buffer);
		float right_weight = sense(sensor_angle, buffer);

		// 0 - 1
		float random_turn = Utilities::hash(x + y + rotation) / 4294967295.0f;

		if (forward_weight > left_weight && forward_weight > right_weight)
			rotation += 0;
		else if (forward_weight < left_weight && forward_weight < right_weight)
			rotation += (random_turn - 0.5) * 2 * turn_speed * delta_time;
		else if (right_weight > forward_weight)
			rotation += random_turn*turn_speed*delta_time;
		else if (left_weight > forward_weight)
			rotation -= random_turn * turn_speed * delta_time;
	}

	void update_position(Buffer<float>* buffer, float delta_time)
	{
		// Moves based on speed & delta time
		x += cosf(rotation) * speed * delta_time;
		y += sinf(rotation) * speed * delta_time;

		unsigned int width = buffer->get_width();
		unsigned int height = buffer->get_height();

		// Randomly turn when hitting wall
		if (x < 0 || x >= width || y < 0 || y >= height)
		{
			x = fmin(width - 1, fmax(0, x));
			y = fmin(height - 1, fmax(0, y));
			// Turns randomly
			rotation += (Utilities::hash((unsigned int)(x+1) * (y+1) * (rotation+1)) / 683565275.417);
		}

		// Reflect off wall
		//if (x < 0 || x >= width)
		//{
		//	rotation = Utilities::PI - rotation; // Reflect the angle horizontally
		//	x = fmin(width - 1, fmax(0, x)); // Correct the position to be within bounds
		//}

		//// Check for collision with the top or bottom boundary
		//if (y < 0 || y >= height)
		//{
		//	rotation = -rotation; // Reflect the angle vertically
		//	y = fmin(height - 1, fmax(0, y)); // Correct the position to be within bounds
		//}
	}

	float sense(float angle, Buffer<float>* buffer)
	{
		float* pixels = buffer->get_pixels();
		angle = rotation + angle;
		unsigned int sensor_center_x = x + cosf(angle) * sensor_offset;
		unsigned int sensor_center_y = y + sinf(angle) * sensor_offset;

		// Find "density" of trails within sensor
		float sum = 0;
		for (int offset_x = -sensor_size; offset_x <= sensor_size; offset_x++)
		{
			for (int offset_y = -sensor_size; offset_y <= sensor_size; offset_y++)
			{
				unsigned int sample_x = sensor_center_x + offset_x;
				unsigned int sample_y = sensor_center_y + offset_y;
				if (sample_x >= 0 && sample_x < buffer->get_width() && sample_y >= 0 && sample_y < buffer->get_height())
				{
					unsigned int i = (sample_y * buffer->get_width() + sample_x) * 4;
					sum += pixels[i + 3];
				}
			}
		}
		return sum;
	}
};