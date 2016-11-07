#include "FPSCounter.hpp"

FPSCounter fpscounter;

FPSCounter::FPSCounter()
	: FPS_Time(0.0),
	  FPS_Frames(0),
	  MAX_ACCUMULATED_TIME(1.0),
	  TIME_STEP(0.02)
{
	accumulator=0.0f;
	DTTicks = clock.getElapsedTime().asMilliseconds();
	Log("Init FPS counter\n");

	gameplaytime = 0;

	CountFPS();
}

FPSCounter::~FPSCounter()
{
	Log("Total time: ",DTNewTicks,"\nFPS: \n");
	unsigned int i=0;
	long long fps =0;
	while(i<fpscontainer.size())
	{
		Log(fpscontainer[i],"; ");
		fps+=fpscontainer[i];
		i++;
	}
	if(!fpscontainer.empty())
	{
		fps =fps/fpscontainer.size();
		Log("\nAverage FPS: ",fps,"\n");
	}
}

void FPSCounter::CountFPS()
{
	//delta time
	DTNewTicks = clock.getElapsedTime().asMilliseconds();
	DeltaTime = DTNewTicks > DTTicks ? (DTNewTicks - DTTicks) / 1000.0f : 0.0f;
	DTTicks = DTNewTicks;

	//FPS
	++FPS_Frames;
	FPS_Time += DeltaTime;
	if (FPS_Time >= 1.0f)
	{
		FPS_Number = FPS_Frames / FPS_Time;
		FPS_Frames = 0;
		FPS_Time = 0.0f;
		fpscontainer.push_back(FPS_Number);
	}
	//fixed step:
	if(accumulator<MAX_ACCUMULATED_TIME)
	{
		accumulator=accumulator+DeltaTime;
	}
}

void FPSCounter::UpdateTime(int delta)
{
	gameplaytime += delta;
}

unsigned int FPSCounter::GetGameplayTime()
{
	return gameplaytime;
}

