#include "PlayerControl.hpp"

#include "Player.hpp"

std::default_random_engine generator;

PlayerControl::PlayerControl(Player* ownerptr, int idowner, ControlType controltype)
	: owner(ownerptr), type(controltype)
{
	ownerid = idowner;

	deltavelocity = resources->GetVariable("velocity_delta");
	minvelocity = resources->GetVariable("velocity_min");
	maxvelocity = resources->GetVariable("velocity_max");
	lossvelocity = resources->GetVariable("velocity_loss");
}

PlayerControl::~PlayerControl()
{

}

ControlType PlayerControl::GetType()
{
	return type;
}

void PlayerControl::SetType(ControlType controltype)
{
	type = controltype;
}

void PlayerControl::SetKeys(sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key shoot)
{
	leftkey = left;
	rightkey = right;
	shootkey = shoot;
}

void PlayerControl::SetActiveJoystick(int id)
{
	joystickNumber = id;
}

void PlayerControl::CheckInput()
{
	switch(type)
	{
		case ControlType::MANUAL:
			CheckManualInput();
			break;
	}
}

void PlayerControl::CheckManualInput()
{
	if (sf::Keyboard::isKeyPressed(leftkey))
		leftpressed = true;
	else
		leftpressed = false;

	if (sf::Keyboard::isKeyPressed(rightkey))
		rightpressed = true;
	else
		rightpressed = false;

	if (sf::Keyboard::isKeyPressed(shootkey))
		shootpressed = true;
	else
		shootpressed = false;

	if (sf::Joystick::isConnected(joystickNumber))
	{
		if (sf::Joystick::getAxisPosition(joystickNumber,sf::Joystick::X)<-50 || sf::Joystick::getAxisPosition(joystickNumber,sf::Joystick::PovX)<-90)
			leftpressed = true;
		else
			leftpressed = false;

		if (sf::Joystick::getAxisPosition(joystickNumber,sf::Joystick::X)>50 || sf::Joystick::getAxisPosition(joystickNumber,sf::Joystick::PovX)>90)
			rightpressed = true;
		else
			rightpressed = false;
		if (sf::Joystick::isButtonPressed(joystickNumber,1))
			shootpressed = true;
		else
			shootpressed = false;
	}
}


void PlayerControl::Update(std::vector<Player*>* players)
{
	switch(type)
	{
		case ControlType::MANUAL:
			UpdateManualMovement();
			UpdateManualBehavior(players);
			break;
	}
}

void PlayerControl::UpdateManualMovement()
{
	if(leftpressed && owner->velocity >= minvelocity)
		owner->velocity -= deltavelocity;
	else if (rightpressed && owner->velocity <= maxvelocity)
		owner->velocity += deltavelocity;

	owner->velocity *= lossvelocity;
}

void PlayerControl::UpdateManualBehavior(std::vector<Player*>* players)
{

}
