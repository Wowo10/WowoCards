#include "Unit.hpp"

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

	std::string s_maxhealth,s_damage,s_velocity,s_range;

	file.close();

	file.open("Data/img/"+name+"/stats.csv", std::ios::in);

	if(!file.good())
		Log("No stats Unit File "+name+"\n");

	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_range); //1st row - headers
	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_range); //data

	maxhealth = std::stoi(s_maxhealth);
	health = maxhealth;
	damage = std::stoi(s_damage);
	velocity = std::stof(s_velocity);
	range = std::stoi(s_range);

	SwitchStance(Stance::MOVING);

	if(course == Course::LEFT)
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("leftstartpos"),posY));
	}
	else
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("rightstartpos"),posY));
	}

	destination = GetPosition();
}

Unit::~Unit()
{

}

/*
void Unit::SwitchStance(Stance stance)
{
	std::cout << "Switching stance!\n";
	this->stance = stance;
	ActiveSheet();
	currentframe = 0;
}

void Unit::ActiveSheet()
{
	std::cout << static_cast<int>(stance) <<" Activating sheet!\n";
	switch(stance)
	{
		case (Stance::MOVING):
			activesheet = &moves;
			break;
		case (Stance::ATTACKING):
			activesheet = &attacks;
			break;
		case (Stance::STANDING):
			activesheet = &stands;
			break;
		case (Stance::DIEING):
			activesheet = &deaths;
			break;
	}

	sf::Vector2f temp = sprite.getPosition();
	sprite = activesheet->spritesheet;
	sprite.setPosition(temp);
	sprite.setTextureRect(sf::IntRect(activesheet->rect.x * currentframe,0,
									  activesheet->rect.x,activesheet->rect.y));

	if(course == Course::RIGHT)
		sprite.setScale(-1.0,1.0);

}
*/

void Unit::Update(float delta_time)
{
	Object::Update(delta_time);
	//moving
	if(stance == Stance::MOVING)
	{
		sf::Vector2f temp = sprite.getPosition();
		if(course == Course::LEFT)
			temp.x +=velocity * delta_time;
		else
			temp.x -=velocity * delta_time;

		if(temp.y != destination.y)
		{
			if(temp.y - destination.y > 0) // we go up
			{
				if(temp.y - velocity * delta_time - destination.y <= 0)
					temp.y = destination.y;
				else
					temp.y -= velocity * delta_time;
			}
			else
			{
				if(temp.y + velocity * delta_time - destination.y >= 0)
					temp.y = destination.y;
				else
					temp.y += velocity * delta_time;
			}

			if(temp.x - destination.x > 0)
			{
				if(temp.x - destination.x <= range)
					StartAttacking();
				else
					StopAttacking();
			}
			else
			{
				if(destination.x - temp.x <= range){
					StartAttacking();
					std::cout << destination.x <<" " << temp.x <<" "<< destination.x - temp.x  <<"\n";
				}
				else
					StopAttacking();
			}

		}
		sprite.setPosition(temp);
	}
}

void Unit::Render(sf::RenderTarget& window)
{
	window.draw(sprite);
}

void Unit::SetPosition(float x,float y)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

void Unit::MoveTo(sf::Vector2f destination)
{
	this->destination = destination;
}

void Unit::ApplyDamage(int damage)
{
	if(stance != Stance::DIEING)
	{
		if(health - damage < 0)
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
