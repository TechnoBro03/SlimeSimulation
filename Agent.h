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
	float sensor_size; // Radius of sensor
	float sensor_angle_offset; // Angle in radians
	float speed; // Speed
	float turn_speed; // Turn speed
	
public:
	Agent(float x, float y, float roation)
	{
		this->x = x; this->y = y; this->rotation = roation;
		sensor_offset = 25;
		sensor_size = 1;
		sensor_angle_offset = .52; // 30 Degrees
		speed = 50; // Pixels per second
		turn_speed = 4;
	}

	void draw(Buffer<float>* buffer)
	{
		buffer->set_pixel(static_cast<unsigned int>(x), static_cast<unsigned int>(y), sf::Color::White);
	}

	void update_rotation(Buffer<float>* buffer, float delta_time)
	{
		float forward_weight = sense(-sensor_angle_offset, buffer);
		float left_weight = sense(0, buffer);
		float right_weight = sense(sensor_angle_offset, buffer);

		// 0 - 1
		float random_turn = Utilities::hash(x + y + rotation) / 4294967295.0f;

		if (forward_weight > left_weight && forward_weight > right_weight)
			rotation += 0;
		/*else if (forward_weight < left_weight && forward_weight < right_weight)
			rotation += (random_turn - 0.5) * 2 * turn_speed * delta_time;*/
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

		// Randomly turn off wall
		//if (x < 0 || x >= width || y < 0 || y >= height)
		//{
		//	x = fmin(width - 1, fmax(0, x));
		//	y = fmin(height - 1, fmax(0, y));
		//	// Turns randomly
		//	rotation += (Utilities::hash((unsigned int)x * y * rotation) / 683565275.417);
		//}

		// Reflect off wall
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

	float sense(float angle, Buffer<float>* buffer)
	{
		float* pixels = buffer->get_pixels();
		float sensor_angle = rotation + angle;
		unsigned int sensor_center_x = x + cosf(sensor_angle) * sensor_offset;
		unsigned int sensor_center_y = y + sinf(sensor_angle) * sensor_offset;

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