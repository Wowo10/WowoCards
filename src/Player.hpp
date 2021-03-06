#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <random>

#include "Utils/Log.hpp"
#include "UnitObject.hpp"
#include "PlayerControl.hpp"


/*****
Object::sprite we can use as invincible bounding box for whole ship
now is still using for camera centering
*****/

enum class PlayerType
{
	PIRATE = 0,
	MLG,
	POLYGON,
	KNIGHT,
	MAGE,
	STICKMAN
};

class Player : public UnitObject
{
	int maxmana,mana;
	int cards = 0;
	int draws = 5;
	float healthregen = 0, manaregen = 0;

	GameTimer castingtimer = 1000;

	public:
		PlayerType playertype;

		PlayerControl control;

		void Cast();
		bool casted = false;
		UnitObject* spelltarget = nullptr;
		void StartCasting();
		void ReleaseSpell();

		//Player(PlayerType typeplayer, int idparam, ControlType controltype);
		Player(int idparam, ControlType controltype,const std::string& name, Course direction);
		~Player();

		void CheckInput();

		void Update(float delta_time) override;
		void Render(sf::RenderTarget& window, bool showids) override;

		void SetPosition(float x, float y) override;

		//ParticleSystem particlesystem;

		void SetHP(short int value);
		int GetHP();

		void ActiveSheet() override;



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

	protected:
		int id;

		float hp;
		float maxhp;
};


#endif
