#ifndef FPSCOUNTER_HPP_INCLUDED
#define FPSCOUNTER_HPP_INCLUDED

#include<fstream>
#include<vector>
#include<map>
#include<cassert>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Utils/Log.hpp"

class FPSCounter
{
		unsigned int gameplaytime;
		sf::Clock clock;
		float FPS_Time, DeltaTime, FPS_Number;
		int FPS_Frames;
		unsigned long DTTicks, DTNewTicks;
		const float MAX_ACCUMULATED_TIME;
		std::vector <int> fpscontainer;
	public:
		float accumulator;
		const float TIME_STEP;
		bool wasPaused;

		FPSCounter();
		~FPSCounter();

		void CountFPS();

		int GetTime()
		{
			return clock.getElapsedTime().asMilliseconds();
		}

		unsigned int GetGameplayTime();
		void UpdateTime(int delta);

};

extern FPSCounter fpscounter;


#endif // FPSCOUNTER_HPP_INCLUDED
