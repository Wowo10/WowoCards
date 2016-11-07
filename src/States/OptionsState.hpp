#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H

#include "GameState.hpp"
#include <SFML/Audio.hpp>
#include "../Object.hpp"
#include "../Options.hpp"


class OptionsState : public GameState
{
	public:
		OptionsState(GameEngine* game);
		~OptionsState();

		void Update(float time_step);
		void HandleEvents(sf::Event& event);
		void Render();

	private:
		void initSettingsState();
		void toggleFullscreen();
		void changeResolution();
		void changeMultisampling();
		void toggleVsync();
		void changeLanguage();
		void changeMusic();
		void changeSound();

		void SaveOptions();

		sf::Sprite background;
		sf::Vector2f backgroundpos;
		tgui::Theme::Ptr mainTheme;
		tgui::VerticalLayout::Ptr layout;
		tgui::VerticalLayout::Ptr settingLayout;
		tgui::Button::Ptr button1,button2,button3,button4,button5,button6,button7,buttonExit,buttonSaveAndExit;
};

#endif // OPTIONSSTATE_H
