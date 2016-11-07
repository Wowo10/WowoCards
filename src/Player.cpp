#include "Player.hpp"

Player::Player(PlayerType typeplayer, int idparam, ControlType controltype)
	: Object(ObjectType::PLAYER),
	  control(this, idparam, controltype)
{
	playertype = typeplayer;
	velocity = 0.0f;

	id = idparam;

	maxhp = 100.0f;
	SetHP(maxhp);

	sprite.setTexture( *resources->GetTexture("ships/ship1", TextureType::SPRITE));

	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	sprite.scale(SCALE, SCALE);

}

Player::~Player()
{

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


void Player::DecreaseHealth(float value)
{
	if(hp > 0) //to prevent double kill same player
	{
		hp -= value;

		if(hp <= 0)
		{
			hp = 0;

			deaths++;
		}
	}
}

void Player::CheckInput()
{
	control.CheckInput();
}

void Player::UpdateMovement()
{
	if(direction > 180.0f)
		direction -= 360.0f;
	else if(direction < -180.0f)
		direction += 360.0f;

	float move_x = cos(PI/180.0f*direction)*velocity;
	float move_y = sin(PI/180.0f*direction)*velocity;

	///
	Move(move_x, move_y);
	sprite.setRotation(direction);
}

void Player::Update(float delta_time)
{
	if(alive)
	{
		UpdateMovement();

		/*
		particlesystem.setPosition(sprite.getPosition());
		particlesystem.update(fpscounter.TIME_STEP);
		particlesystem.fuel(50);*/
	}
}

void Player::Render(sf::RenderTarget& window)
{
	if(alive)
	{
		window.draw(sprite);

		//window.draw(sprite);
		//window.draw(ship.parts[PartLocation::BODY].sprite);

		//window.draw(particlesystem);
	}
}

void Player::SetPosition(float x, float y)
{
	sf::Vector2f pos(x, y);
	sprite.setPosition(x, y);
}

void Player::SetDirection(float value)
{
	direction = value;
	sprite.setRotation(direction);
}

int Player::GetID()
{
	return id;
}


void Player::Enable(bool value)
{
	alive = value;
}


void Player::Spawn(sf::Vector2f pos)
{
	SetPosition(pos.x, pos.y);
	alive = true;
	SetHP(maxhp);

	velocity = 0.0f;
}


void Player::Hit(Player* enemy)
{
	if(enemy->GetHP() > 0)
	{
		enemy->DecreaseHealth(500);

		if(enemy->GetHP() == 0)
		{
			kills++;
		}
	}
}

void Player::Kill()
{
	alive = false;
}
