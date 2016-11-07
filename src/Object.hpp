#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Collision.hpp"

#include "Utils/Log.hpp"
#include "FPSCounter.hpp"
#include "GameTimer.hpp"
#include "ResourceManager.hpp"



extern int MAP_SIZE_X;
extern int MAP_SIZE_Y;

enum class ObjectType
{
	PLAYER,
	POWERUP,
	OBSTACLE,
	SPAWNPOINT,
	BUTTON,
	UNIT
};


class Object
{
	public:
		Object(ObjectType objtype, std::string name, int owner_id = -1);
		Object(ObjectType objtype);
		Object(ObjectType objtype, std::string graphic, sf::Vector2f pos);
		virtual ~Object();

		ObjectType type;

		sf::Sprite sprite;

		int owner = -1;

		sf::Vector2f GetPosition();
		virtual void SetPosition(float x, float y);
		void Move(float x, float y);
		virtual void SetDirection(float value);

		void SetSprite(const std::string& name);

		float velocity = 0;
		float direction = 0;

	virtual void Update(float delta_time);
		virtual void Render(sf::RenderTarget& window);


		bool todelete = false;

	protected:
		float rotation=0;
};


#endif

