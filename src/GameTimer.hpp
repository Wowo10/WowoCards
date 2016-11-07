#ifndef GAMETIMER_HPP_INCLUDED
#define GAMETIMER_HPP_INCLUDED

#include "FPSCounter.hpp"

class GameTimer
{
		unsigned int timer;// In miliseconds
	public:

		GameTimer(unsigned int start_shift = 0)
		{
			timer = fpscounter.GetGameplayTime() + start_shift;
		}

		GameTimer& operator = (int shift)
		{
			timer = fpscounter.GetGameplayTime() + shift;
			return *this;
		}

		bool Passed()
		{
			if(timer < fpscounter.GetGameplayTime())
				return true;
			else
				return false;
		}

		void AddDelta(unsigned int value)
		{
			timer = fpscounter.GetGameplayTime() + value;
		}

		int GetTime()//Returns time left
		{
			return timer-fpscounter.GetGameplayTime();
		}


		~GameTimer() { }
};


#endif // GAMETIMER_HPP_INCLUDED
