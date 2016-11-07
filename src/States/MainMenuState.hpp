#ifndef MAINMENUSTATE_H_INCLUDED
#define MAINMENUSTATE_H_INCLUDED

#include "GameState.hpp"
#include "../Button.hpp"
#include <SFML/Audio.hpp>
#include "../Object.hpp"

#define MAX_ELEMENTS 5

class MainMenuState : public GameState
{
	public:
		MainMenuState(GameEngine* game);
		~MainMenuState();

		void Update(float time_step);
		void HandleEvents(sf::Event& event);
		void Render();
		sf::Music main_theme;

	protected:

		std::vector<Button*> buttons;
		tgui::VerticalLayout::Ptr main_layout;
		tgui::Theme::Ptr menu_theme;
		sf::Sprite logo_sprite;
		sf::Sprite background;
		OrientedBoundingBox mouse_box;


		sf::Vector2f backgroundpos;
};

#endif // MAINMENUSTATE_H_INCLUDED
