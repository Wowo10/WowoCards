#include "GameEngine.hpp"


int main()
{
	bool restart = false;

	do
	{
		GameEngine game;

		while( !game.exit)
		{
			game.Update();
		}

		restart = game.restart;
	}
	while(restart);

	return 0;
}
