#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "GameState.hpp"
#include <SFML/Audio.hpp>
#include "../Object.hpp"
#include <string>

#define CREDITSLINES 9
class CreditsState : public GameState
{
	public:
		CreditsState(GameEngine* game);
		~CreditsState();

		void Update(float time_step);
		void HandleEvents(sf::Event& event);
		void Render();

	private:
		sf::Sprite background;
		sf::Vector2f backgroundpos;
		tgui::TextBox::Ptr creditsTextBox;
		tgui::Theme::Ptr mainTheme;
};

#endif // CREDITSSTATE_H
