#include "AnimatedObject.hpp"

AnimatedObject::AnimatedObject(const std::string& name, Course direction, ObjectType type)
	: Object(type, direction)
{
	this->name = name;
	stance = Stance::NONE;

	SetBounds();
}

AnimatedObject::~AnimatedObject()
{

}

void AnimatedObject::SetBounds()
{
	auto rect = sprite.getLocalBounds();
	sprite.setOrigin(rect.width / 2.0f, rect.height);
}

void AnimatedObject::ActiveSheet()
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

void AnimatedObject::SwitchStance(Stance stance)
{
//	std::cout << "ID: " << id << " Stance: "<<static_cast<int>(stance) <<"\n";

	if(stance != this->stance && this->stance != Stance::DIEING)
	{
		auto temp = sheets.find(stance);

		if(temp != sheets.end())
		{
			this->stance = stance;

			ActiveSheet();
		}
		else
		{
			std::cout << "No Such sheet: "<<stance<<"\n";
		}
	}
}

void AnimatedObject::Update(float delta_time)
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

void AnimatedObject::Render(sf::RenderTarget& window)
{
	window.draw(sprite);
}
