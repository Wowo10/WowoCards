#ifndef REALTIMER_HPP_INCLUDED
#define REALTIMER_HPP_INCLUDED

#include "FPSCounter.hpp"

class RealTimer
{
		sf::Clock clock;
		sf::Time time_to_count;
	public:
		RealTimer()
		{
			this->time_to_count = sf::seconds(90);
		}
		RealTimer(float count_to)
		{
			this->time_to_count = sf::seconds(count_to);
		}
		RealTimer& operator = (float count_to)
		{
			this->time_to_count = sf::seconds(count_to);
			return *this;
		}

		bool Passed()
		{
			if(clock.getElapsedTime() > time_to_count)
				return true;
			else
				return false;
		}

		void RestartTimer()
		{
			clock.restart();
		}
		void RestartTimer(float count_to)
		{
			this->time_to_count = sf::seconds(count_to);
			clock.restart();
		}
		float GetCurrentTime()
		{
			return clock.getElapsedTime().asSeconds();
		}

		int GetTimeLeft()
		{
			int temp_value = floor(time_to_count.asSeconds()-clock.getElapsedTime().asSeconds());
			return temp_value;
		}

		~RealTimer() { }
};


#endif // REALTIMER_HPP_INCLUDED

