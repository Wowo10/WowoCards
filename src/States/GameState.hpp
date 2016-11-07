#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include "../GameEngine.hpp"

class GameState
{
	public:
		GameState(GameEngine* game)
			: engine(game),
			  gui(game->window)
		{}
		virtual ~GameState() {}

		GameState(const GameState&) = delete;
		GameState& operator=(const GameState&) = delete;


		virtual void Update(float time_step) = 0;
		virtual void HandleEvents(sf::Event& event) = 0;
		virtual void Render() = 0;


	protected:
		GameEngine* engine;
		tgui::Gui gui;
};


#endif //GAMESTATE_HPP_INCLUDED
