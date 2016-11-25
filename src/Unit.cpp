#include "Unit.hpp"

int Unit::ID = 0;

Unit::Unit(const std::string& name, Course direction, int posY)
	: Object(ObjectType::UNIT, name,direction)
{
	//this->frametime = frametime;

	stance = Stance::MOVING;
	attacking = false;

	std::string s_frametime,s_attack,s_death,s_move,s_stand;

	std::fstream file;
	file.open("Data/img/"+name+"/animation.csv", std::ios::in);

	if(!file.good())
		Log("No animations Unit File "+name+"\n");

	ReadRowFromCSV(file, s_frametime,s_attack,s_death,s_move,s_stand); //1st row - headers
	ReadRowFromCSV(file, s_frametime,s_attack,s_death,s_move,s_stand); //data

	if(s_frametime == "0")
		s_frametime = "100";

	/* OLD VERSION
		attacks = Sheet(name+"/attack",std::stoi(s_attack));
		moves = Sheet(name+"/move",std::stoi(s_move));
		deaths = Sheet(name+"/death",std::stoi(s_death));
		stands = Sheet(name+"/stand",std::stoi(s_stand));
		*/

	frametime = std::stoi(s_frametime);


	sheets[Stance::ATTACKING] = Sheet(name+"/attack",std::stoi(s_attack));
	sheets[Stance::MOVING] = Sheet(name+"/move",std::stoi(s_move));
	sheets[Stance::DIEING] = Sheet(name+"/death",std::stoi(s_death));
	sheets[Stance::STANDING] = Sheet(name+"/stand",std::stoi(s_stand));

	std::string s_maxhealth,s_damage,s_velocity,s_range,s_attackdealey;

	file.close();

	file.open("Data/img/"+name+"/stats.csv", std::ios::in);

	if(!file.good())
		Log("No stats Unit File "+name+"\n");

	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_range,s_attackdealey); //1st row - headers
	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_range,s_attackdealey); //data

	maxhealth = std::stoi(s_maxhealth);
	health = maxhealth;
	damage = std::stoi(s_damage);
	velocity = std::stof(s_velocity);
	range = std::stoi(s_range);
	attackdealey = std::stof(s_attackdealey);

	SwitchStance(Stance::MOVING);

	if(course == Course::LEFT)
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("leftstartpos"),posY));
	}
	else
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("rightstartpos"),posY));
	}

	id = ID++;

	TID.setFont(resources->font);
	TID.setPosition(GetPosition());
	TID.setCharacterSize(12);
	TID.setString(to_string(id));
}

Unit::~Unit()
{

}

void Unit::Update(float delta_time)
{
	Object::Update(delta_time);
	//moving
	if(stance == Stance::MOVING)
	{
		sf::Vector2f temp = sprite.getPosition();

		if(target == nullptr)
		{
			if(course == Course::LEFT)
				temp.x +=velocity * delta_time;
			else
				temp.x -=velocity * delta_time;
		}
		else
		{
			float distanceX = target->GetPosition().x - GetPosition().x;
			if(distanceX < 0)
				distanceX *=-1;

			float distanceY = target->GetPosition().y - GetPosition().y;

			if(distanceX > range)
			{
				if(course == Course::LEFT)
					temp.x +=velocity * delta_time;
				else
					temp.x -=velocity * delta_time;
			}
			else if(distanceY == 0)
				SwitchStance(Stance::ATTACKING);

			if(distanceY < 0)
				if(distanceY >= -1)
					temp.y = target->GetPosition().y;
				else
					temp.y -= velocity * delta_time;
			else if(distanceY <= 1)
				temp.y = target->GetPosition().y;
			else
				temp.y += velocity * delta_time;
		}
		sprite.setPosition(temp);
	}
	else if(stance == Stance::ATTACKING)
	{
		if(currentframe == sheets[stance].maxframes/2 && !attacked)
		{
			target->ApplyDamage(damage);
			attacked = true;
		}
		if(currentframe == sheets[stance].maxframes -1)
		{
			attacked = false;

			attacktimer.AddDelta(attackdealey);
			SwitchStance(Stance::STANDING);
		}
	}
	else if(stance == Stance::STANDING)
	{
		if(true)//stuns etc (todo)
		{
			if(attacktimer.Passed())
				SwitchStance(Stance::ATTACKING);
			if(target == nullptr)
				SwitchStance(Stance::MOVING);
		}
	}

	if(target!= nullptr && target->IsDieing() && stance != Stance::DIEING)
	{
		target = nullptr;
		SwitchStance(Stance::MOVING);
	}

	TID.setPosition(GetPosition());
}

void Unit::Render(sf::RenderTarget& window)
{
	window.draw(sprite);
	window.draw(TID);
}

void Unit::ActiveSheet()
{
	Object::ActiveSheet();
	ShowDamage();
}

void Unit::SetPosition(float x,float y)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

bool Unit::IsDieing()
{
	return stance==Stance::DIEING;
}

bool Unit::HasTarget()
{
	return target != nullptr;
}

void Unit::SetTarget(Unit* unit)
{
	target = unit;
	unit->target = this;
}

void Unit::ApplyDamage(int damage)
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

void Unit::ShowDamage()
{
	float value = 255-(float)(maxhealth-health)/maxhealth*255;

	sprite.setColor(sf::Color(255,value,value));
}
