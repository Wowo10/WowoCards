#include "Object.hpp"

int MAP_SIZE_X=1000;
int MAP_SIZE_Y=1000;


Object::Object(ObjectType objtype, std::string name, int owner_id)
{
	type = objtype;
	owner = owner_id;

	SetSprite(name);
}

Object::Object(ObjectType objtype, std::string name, sf::Vector2f pos)
{
	type = objtype;
	owner = -1;

	SetSprite(name);
	sprite.setPosition(pos);
}


Object::Object(ObjectType objtype)
{
	type = objtype;
	owner = -1;
}


Object::~Object()
{

}


void Object::Update(float delta_time)
{

}

void Object::Render(sf::RenderTarget& window)
{
	window.draw(sprite);
}

sf::Vector2f Object::GetPosition()
{
	return sprite.getPosition();
}

void Object::SetPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Object::Move(float x, float y)
{
	sprite.move(x, y);
}

void Object::SetDirection(float value)
{
	direction = value;

	sprite.setRotation(direction);
}

void Object::SetSprite(const std::string& name)
{
	sprite.setTexture( *resources->GetTexture(name, TextureType::SPRITE));

	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
}
