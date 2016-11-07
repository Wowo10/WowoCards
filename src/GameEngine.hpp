#ifndef GAMEENGINE_HPP_INCLUDED
#define GAMEENGINE_HPP_INCLUDED

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "Options.hpp"

const float DEGTORAD = 0.017453f;
const float RADTODEG = 57.295779f;

class GameState;

enum GameModes
{
	DEATHMATCH,
	TEAM_DEATHMATCH,
	CTF
};

enum class StateOperation
{
	PUSH,
	CHANGE,
	POP,
	CLEAN,
	NONE
};

class GameEngine
{
	public:
		bool exit = false;
		bool restart = false;

		Options options;

		sf::RenderWindow window;

		std::random_device randomdevice;
		std::mt19937 gen;

		GameEngine();
		~GameEngine();

		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();

		void Update();
		void Exit();


	private:
		std::deque< std::unique_ptr<GameState> > states;
		StateOperation nextoperation = StateOperation::NONE;
		GameState* changestate;

		void Init();

		void HandleEvents();
		void Render();
};

#endif //GAMEENGINE_HPP_INCLUDED
