#include "UnitObject.hpp"

int UnitObject::ID = 0;

UnitObject::UnitObject(const std::string& name, Course direction, ObjectType type)
	: Object(type, name,direction)
{
	id = ID++;

	stance = Stance::NONE;

	SetBounds();

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

void UnitObject::SwitchStance(Stance stance)
{
	//std::cout << "ID: " << id << " Stance: "<<static_cast<int>(stance) <<"\n"; DEBUG

	Object::SwitchStance(stance);
}

bool UnitObject::IsDieing()
{
	if(id < 0)
		std::cout << "ID: " << id <<" Stance: "<<this->stance<<"\n";// Was bug with ID & state -892389123

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

void UnitObject::SetBounds()
{
	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height);
}
