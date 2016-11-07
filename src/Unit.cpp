#include "Unit.hpp"

Unit::Unit(const std::string& name, Course direction, int frametime) : Object(ObjectType::UNIT)
{
	this->name = name;
	this->course = direction;
	this->frametime = frametime;

	stance = Stance::MOVING;
	attacking = false;
	currentframe = 0;

	std::string s_maxhealth,s_damage,s_velocity,s_attack,s_death,s_move,s_stand;

	std::fstream file;
	file.open("Data/img/"+name+"/stats.csv", std::ios::in);

	if(!file.good())
		Log("No Such Unit File "+name+"\n");
	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_attack,s_death,s_move,s_stand); //1st row - headers
	ReadRowFromCSV(file, s_maxhealth,s_damage,s_velocity,s_attack,s_death,s_move,s_stand); //data


	maxhealth = std::stoi(s_maxhealth);
	health = maxhealth;
	damage = std::stoi(s_damage);
	velocity = std::stof(s_velocity);

	attacks = Sheet(name+"/attack",std::stoi(s_attack));
	moves = Sheet(name+"/move",std::stoi(s_move));
	deaths = Sheet(name+"/death",std::stoi(s_death));
	stands = Sheet(name+"/stand",std::stoi(s_stand));


	ActiveSheet();

	if(course == Course::LEFT)
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("leftstartpos"),300));
	}
	else
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("rightstartpos"),300));
	}
}

Unit::~Unit()
{

}

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

void Unit::Update(float delta_time)
{
	//moving
	if(stance == Stance::MOVING)
	{
		sf::Vector2f temp = sprite.getPosition();
		if(course == Course::LEFT)
			temp.x +=velocity * delta_time;
		else
			temp.x -=velocity * delta_time;


		sprite.setPosition(temp);
	}

	if(animationtimer.Passed())
	{
		if(currentframe + 1 == activesheet->maxframes)
		{
			if(stance == Stance::DIEING)
				todelete = true;
			else
				currentframe = 0;
		}
		else
			++currentframe;

		sprite.setTextureRect(sf::IntRect(activesheet->rect.x * currentframe,0,
										  activesheet->rect.x,activesheet->rect.y));

		animationtimer.AddDelta(frametime);
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

void Unit::SetDirection(float value)
{

}

void Unit::ApplyDamage(int damage)
{
	if(stance != Stance::DIEING)
	{
		if(health - damage < 0)
		{
			std::cout << "Dieing! \n";
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
