#include "Object.hpp"
#include "Utils/FileUtils.hpp"
#include "GameTimer.hpp"

enum Course
{
	LEFT = 0,
	RIGHT
};

enum Stance
{
	MOVING = 0,
	STANDING,
	ATTACKING,
	DIEING
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

class Unit : public Object
{
		std::string name;
		int health, maxhealth;
		int damage;
		Stance stance;

		Course course;
		GameTimer animationtimer;
		int currentframe;
		int frametime;

		Sheet attacks,moves,deaths,stands;
		Sheet* activesheet;

		void ActiveSheet();

		sf::Sprite sprite;
	public:
		Unit(const std::string& name,Course direction, int frematime);
		~Unit();

		/*
		void Update(); //override;
		void Render(sf::RenderTarget& window); //override;
		*/

		void SwitchStance(Stance stance);

		//bool todelete;
		bool attacking;

		void Update(float frame_time) override;
		void Render(sf::RenderTarget& window) override;

		void SetPosition(float x, float y) override;
		void SetDirection(float value) override;

		void ApplyDamage(int damage);
		void ShowDamage();

		void StartAtacking()
		{
			attacking = true;
			SwitchStance(Stance::ATTACKING);
		}

		void StopAttacking()
		{
			attacking = false;
			SwitchStance(Stance::MOVING);
		}
};
