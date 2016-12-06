#ifndef GAMEPLAYSTATE_HPP_INCLUDED
#define GAMEPLAYSTATE_HPP_INCLUDED

#include "GameState.hpp"

#include <SFML/Audio.hpp>
#include <ctime>

#include "../Object.hpp"
#include "../Player.hpp"
#include "../Plane.hpp"
#include "../Unit.hpp"
#include "../RealTimer.hpp"

#include "../Camera.hpp"


class GameplayState : public GameState
{
	public:
		GameplayState(GameEngine* game);
		~GameplayState();

		void Update(float time_step);
		void HandleEvents(sf::Event& event);
		void Render();

		RealTimer timer;

	protected:
		std::mt19937 gen;

		Plane* plane;

		int rounds = 0;

		float timemultiplier = 1.0f;

		Camera camera;

		std::vector<Player*> players;
		std::vector<Object*> objects;
		std::vector<Unit*> units;

		int playerid = 0;

		sf::Music main_theme;
		sf::SoundBuffer sd_buffer;
		std::vector<sf::Sound*> screams;

		std::vector<sf::Sprite> guielements;
		std::vector<sf::Text> texts;
		bool showgui = true;
		bool showendgui = false;
		bool showids = true;
		tgui::Gui end_gui;
		tgui::Theme::Ptr gui_theme;

		Player* AddPlayer(PlayerType type, ControlType controltype);

		void UpdateObjects(float gametime);
		void CheckCollisions(float gametime);

		int starttimer;

		void RenderMapToActiveView(); //render map and obiects to active viewport
		void RenderObjectsToActiveView(); //helper for RenderMapToActiveView(); render only obiects

		void KillPlayer(Player* player);
};


#endif //GameplayState_HPP_INCLUDED
