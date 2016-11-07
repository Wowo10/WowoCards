#ifndef PLAYERCONTROL_HPP_INCLUDED
#define PLAYERCONTROL_HPP_INCLUDED

#include <random>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Joystick.hpp"

#include "Utils/Log.hpp"
#include "FPSCounter.hpp"

enum class ControlType
{
	MANUAL,
	NONE
};

class Player;

class PlayerControl
{
	public:
		float deltavelocity, minvelocity, maxvelocity, lossvelocity;

		PlayerControl(Player* ownerptr, int idowner, ControlType controltype = ControlType::NONE);
		~PlayerControl();

		ControlType GetType();
		void SetType(ControlType controltype);

		void SetKeys(sf::Keyboard::Key leftkey, sf::Keyboard::Key rightkey, sf::Keyboard::Key shootkey);
		void SetActiveJoystick(int id);

		void CheckInput();
		void Update(std::vector<Player*>* players);
		bool isSpecialPressed()
		{
			return shootpressed;
		}


	protected:
		int ownerid = -1;
		Player* owner;
		ControlType type;
		sf::Keyboard::Key leftkey, rightkey, shootkey;

		int joystickNumber;
		bool leftpressed;
		bool rightpressed;
		bool shootpressed = false;


		void CheckManualInput();
		void UpdateManualMovement();
		void UpdateManualBehavior(std::vector<Player*>* players);
};




#endif
