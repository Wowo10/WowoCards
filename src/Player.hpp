#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <random>

#include "Utils/Log.hpp"
#include "Object.hpp"
#include "PlayerControl.hpp"


/*****
Object::sprite we can use as invincible bounding box for whole ship
now is still using for camera centering
*****/

enum class PlayerType
{
	SHIP,
	AIRCRAFT,
	SUBMARINE
};

class Player : public Object
{
	public:
		PlayerType playertype;

		PlayerControl control;

		unsigned int kills = 0;
		unsigned int deaths = 0;

		float defaultvelocity;

		GameTimer deathtimer;

		Player(PlayerType typeplayer, int idparam, ControlType controltype);
		~Player();

		void CheckInput();

		void Update(float delta_time) override;
		void Render(sf::RenderTarget& window) override;

		void SetPosition(float x, float y) override;

		bool alive = true;
		bool can_shoot = true;

		//ParticleSystem particlesystem;

		void SetHP(short int value);
		int GetHP();
		void DecreaseHealth(float value);

		/****
		Should replace by one CheckCollision() method
		with pixel perfect testing only parts, which colliding by bounding box
		****/
		bool CheckBoundingBoxTest(sf::Sprite& enemy)
		{
			if(Collision::BoundingBoxTest(sprite, enemy))
				return true;

			return false;
		}

		bool CheckBoundingBoxTest(const OrientedBoundingBox& enemy)
		{
			if(Collision::BoundingBoxTest(OrientedBoundingBox(sprite), enemy))
				return true;

			return false;
		}

		bool CheckPixelPerfectTest(sf::Sprite& enemy)
		{
			if(Collision::PixelPerfectTest(sprite, enemy))
				return true;

			return false;
		}

		bool CheckPixelPerfectTest(sf::Vector2f& point)
		{
			if(Collision::PixelPerfectTest(sprite, point))
				return true;

			return false;
		}

		void Spawn(sf::Vector2f pos);

		void Hit(Player* enemy);
		void Kill();


	protected:
		int id;

		float hp;
		float maxhp;
};


#endif
