#pragma once

#include <thread>
#include <chrono>

#include "utils.h"
#include "AgentHandler.h"
#include "Renderer.h"
#include "Processing.h"


class Simulation
{
public:
	inline static s::Uint numThreads;
private:
	inline static std::thread *threads;

	static void updateSimulation()
	{
		// Do something, probably all will be within agent_handler? How do we make the sim deal with threads, not agent_handler?
		// Start/stop points?
		// Update agents
		// evaporate and decay
		
		/*AgentHandler::updateAgents(0, AgentHandler::numAgents);
		Processing::process(0, Renderer::width * Renderer::height*4);*/
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		for (int i = 0; i < numThreads; i++)
		{
			s::Uint start = AgentHandler::numAgents * ((double)i / numThreads);
			s::Uint stop = AgentHandler::numAgents * ((double)(i + 1) / numThreads);
			threads[i] = std::thread(AgentHandler::updateAgents, start, stop);
		}
		for (int i = 0; i < numThreads; i++)
		{
			threads[i].join();
		}
		for (int i = 0; i < numThreads; i++)
		{
			s::Uint start = (Renderer::width * Renderer::height*4) * ((double)i / numThreads);
			s::Uint stop = (Renderer::width * Renderer::height*4) * ((double)(i + 1) / numThreads);
			threads[i] = std::thread(Processing::process, start, stop);
		}
		for (int i = 0; i < numThreads; i++)
		{
			threads[i].join();
		}
	}

public:
	~Simulation()
	{
		delete[] threads;
	}

	static void setParameters(s::Uint numThreads = 0)
	{
		if (numThreads == 0 || numThreads > std::thread::hardware_concurrency())
		{
			Simulation::numThreads = std::thread::hardware_concurrency();
		}
		else
		{
			Simulation::numThreads = numThreads;
		}
		threads = new std::thread[numThreads];
	}

	static void Start()
	{
		while(Renderer::updateWindow())
		{
			updateSimulation();
		}
	}
};