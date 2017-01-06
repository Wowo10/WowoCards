#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Collision.hpp"

#include "Utils/Log.hpp"
#include "FPSCounter.hpp"
#include "GameTimer.hpp"
#include "ResourceManager.hpp"
#include "Utils/FileUtils.hpp"

enum class ObjectType
{
	PLAYER = 0,
	BULLET,
	OBSTACLE,
	BUILDING,
	BUTTON,
	UNIT
};

enum Course
{
	LEFT = 0,
	RIGHT
};

class Object
{
	public:
		Object(ObjectType objtype, std::string name, int owner_id = -1);
		Object(ObjectType objtype);
		Object(ObjectType objtype, std::string graphic, sf::Vector2f pos);
		Object(ObjectType objtype, std::string path, Course direction);
		Object(ObjectType objtype, Course direction);

		virtual ~Object();

		ObjectType type;

		std::string name;

		Course course;

		sf::Sprite sprite;

		int owner = -1;

		sf::Vector2f GetPosition();
		virtual void SetPosition(float x, float y);
		void Move(float x, float y);

		void MoveTo(sf::Vector2f destination);

		void SetSprite(const std::string& name);

		float velocity = 0;

		virtual void Update(float delta_time);
		virtual void Render(sf::RenderTarget& window);

		bool todelete = false;

	protected:
		float rotation=0;
};


#endif

