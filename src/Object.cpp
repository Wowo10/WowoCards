#include "Object.hpp"

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

Object::Object(ObjectType objtype, std::string path, Course direction)
{
	this->type = objtype;
	this->name = path;
	this->course = direction;

	owner = -1;

	currentframe = 0;
}


Object::~Object()
{

}

void Object::ActiveSheet()
{
	currentframe = 0;

	sf::Vector2f temp = sprite.getPosition();
	sprite = sheets[stance].spritesheet;
	sprite.setPosition(temp);
	sprite.setTextureRect(sf::IntRect(sheets[stance].rect.x * currentframe,0,
									  sheets[stance].rect.x,sheets[stance].rect.y));

	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height);

	if(course == Course::RIGHT)
		sprite.setScale(-1.0,1.0);
}

void Object::SwitchStance(Stance stance)
{
//	std::cout << "Stance: "<<static_cast<int>(stance) <<"\n";

	auto temp = sheets.find(stance);

	if(temp != sheets.end())
	{
		this->stance = stance;

		ActiveSheet();
	}
	else
	{
		std::cout << "No Such sheet!\n";
	}
}

void Object::Update(float delta_time)
{
	if(animationtimer.Passed())
	{
		if(currentframe + 1 == sheets[stance].maxframes)
		{
			if(stance == Stance::DIEING)
				todelete = true;
			else
				currentframe = 0;
		}
		else
			++currentframe;

		sprite.setTextureRect(sf::IntRect(sheets[stance].rect.x * currentframe,0,
										  sheets[stance].rect.x,sheets[stance].rect.y));

		animationtimer.AddDelta(frametime);
	}
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

void Object::SetSprite(const std::string& name)
{
	sprite.setTexture( *resources->GetTexture(name, TextureType::SPRITE));

	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height);
}
