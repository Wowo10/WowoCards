#ifndef ANIMATEDOBJECT_HPP_INCLUDED
#define ANIMATEDOBJECT_HPP_INCLUDED

#include "Object.hpp"


enum Stance
{
	NONE = 0,
	MOVING,
	STANDING,
	ATTACKING,
	DIEING,
	CASTING,
	RELEASE
};

struct Sheet
{
	sf::Sprite spritesheet;
	sf::Vector2f rect;
	int maxframes;
	Sheet(const std::string& path, int framescount)
	{
		spritesheet.setTexture(*resources->GetTexture(path));
		maxframes = framescount;
		rect.x = (int)spritesheet.getGlobalBounds().width/framescount;
		rect.y = spritesheet.getGlobalBounds().height;
	}
	Sheet()
	{

	}
};

class AnimatedObject : public Object
{
	public:
		AnimatedObject(const std::string& name, Course direction, ObjectType type);

		~AnimatedObject();

		std::map<Stance, Sheet> sheets;

		GameTimer animationtimer;

		int currentframe;
		int frametime;

		Stance stance;

		virtual void ActiveSheet();
		virtual void SwitchStance(Stance stance);

		void SetBounds();

		virtual void Update(float frame_time) override;
		virtual void Render(sf::RenderTarget& window);
};

#endif //ANIMATEDOBJECT_HPP_INCLUDED
