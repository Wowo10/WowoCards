#include "UnitObject.hpp"

int UnitObject::ID = 0;

UnitObject::UnitObject(const std::string& name, Course direction, ObjectType type)
	: Object(type, name,direction)
{
	id = ID++;

	TID.setFont(resources->font);
	TID.setPosition(GetPosition());
	TID.setCharacterSize(12);
	TID.setString(to_string(id));
}

UnitObject::~UnitObject()
{

}

void UnitObject::Update(float delta_time)
{
	Object::Update(delta_time);
	//moving

	TID.setPosition(GetPosition());
}

void UnitObject::Render(sf::RenderTarget& window, bool showids)
{
	if(showids)
		window.draw(TID);
}

void UnitObject::ActiveSheet()
{
	Object::ActiveSheet();
}

void UnitObject::SetPosition(float x,float y)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

bool UnitObject::IsDieing()
{
	return stance==Stance::DIEING;
}

void UnitObject::ApplyDamage(int damage)
{
	if(stance != Stance::DIEING)
	{
		if(health - damage <= 0)
		{
			health = 0;
			SwitchStance(Stance::DIEING);
		}
		else
			health -= damage;

		ShowDamage();
	}
}

void UnitObject::ShowDamage()
{
	float value = 255-(float)(maxhealth-health)/maxhealth*255;

	sprite.setColor(sf::Color(255,value,value));
}
