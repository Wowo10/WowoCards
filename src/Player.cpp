#include "Player.hpp"

Player::Player(int idparam, ControlType controltype,const std::string& name, Course direction)
	: UnitObject(name, direction, ObjectType::PLAYER),
	  control(this, idparam, controltype)
{
	velocity = 0.0f;

	id = idparam;

	std::string s_frametime,s_stand,s_death,s_casting,s_release;

	std::fstream file;
	file.open("Data/characters/"+name+"/animation.csv", std::ios::in);

	if(!file.good())
	{
		Log("No animations Character File "+name+"\n");
		std::cout << "No anim file!\n";
	}

	ReadRowFromCSV(file, s_frametime,s_stand,s_death,s_casting,s_release); //1st row - headers
	ReadRowFromCSV(file, s_frametime,s_stand,s_death,s_casting,s_release); //data

	if(s_frametime == "0")
		s_frametime = "100";

	frametime = std::stoi(s_frametime);


	sheets[Stance::STANDING] = Sheet("characters/"+name+"/stand",std::stoi(s_stand));
	sheets[Stance::DIEING] = Sheet("characters/"+name+"/death",std::stoi(s_death));
	sheets[Stance::RELEASE] = Sheet("characters/"+name+"/release",std::stoi(s_release));
	sheets[Stance::CASTING] = Sheet("characters/"+name+"/casting",std::stoi(s_casting));

	std::string s_maxhealth,s_maxmana,s_healthregen,s_manaregen;

	file.close();

	file.open("Data/characters/"+name+"/stats.csv", std::ios::in);

	if(!file.good())
		Log("No stats Character File "+name+"\n");

	ReadRowFromCSV(file, s_maxhealth,s_maxmana,s_healthregen,s_manaregen); //1st row - headers
	ReadRowFromCSV(file, s_maxhealth,s_maxmana,s_healthregen,s_manaregen); //data

	maxhealth = std::stoi(s_maxhealth);
	health = maxhealth;
	maxmana = std::stoi(s_maxmana);
	mana = maxmana;
	healthregen = std::stof(s_healthregen);
	manaregen = std::stof(s_manaregen);

	SwitchStance(Stance::STANDING);

	if(course == Course::LEFT)
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("leftstartpos")-50,300));
	}
	else
	{
		sprite.setPosition(sf::Vector2f(resources->GetVariable("rightstartpos")+50,300));
	}
}

Player::~Player()
{

}

void Player::StartCasting()
{
	if(spelltarget == nullptr)
		SwitchStance(Stance::CASTING);
}

void Player::ReleaseSpell()
{
	SwitchStance(Stance::RELEASE);
	//spelltarget.ApplyDamage(1/*spelldmg*/); later
	spelltarget = nullptr;
}

void Player::SetHP(short int value)
{
	hp = value;
	if (hp > maxhp)
		hp = maxhp;
	else if (hp <= 0.0f)
		hp = 0.0f;
}

int Player::GetHP()
{
	return hp;
}


void Player::CheckInput()
{
	control.CheckInput();
}

void Player::Update(float delta_time)
{
	UnitObject::Update(delta_time);
	/*
	particlesystem.setPosition(sprite.getPosition());
	particlesystem.update(fpscounter.TIME_STEP);
	particlesystem.fuel(50);*/
	if(stance == Stance::RELEASE)
	{
		if(currentframe == sheets[stance].maxframes - 2 && !casted)
		{
			//Spell.Effect(target)
			//target->ApplyDamage(damage);
			casted = true;
		}
		if(currentframe == sheets[stance].maxframes -1)
		{
			casted = false;

			//attacktimer.AddDelta(attackdealey);
			SwitchStance(Stance::STANDING);
		}
	}

}

void Player::Render(sf::RenderTarget& window, bool showids)
{
	window.draw(sprite);

	UnitObject::Render(window, showids);
	//window.draw(sprite);
	//window.draw(ship.parts[PartLocation::BODY].sprite);

	//window.draw(particlesystem);

}

void Player::ActiveSheet()
{
	UnitObject::ActiveSheet();
	ShowDamage();
}

void Player::SetPosition(float x, float y)
{
	sf::Vector2f pos(x, y);
	sprite.setPosition(x, y);
}
