#include "Object.hpp"

class Unit : public Object
{
		int health, maxhealth;
		int damage, range;
		float attackdealey;
		bool attacked = false;

		sf::Text TID;

		GameTimer attacktimer;

		Unit* target = nullptr;

		//sf::Sprite sprite;
	public:
		Unit(const std::string& name,Course direction, int posY);
		~Unit();

		bool attacking;

		static int ID;
		int id;

		void Update(float frame_time); //override;
		void Render(sf::RenderTarget& window) override;

		void SetPosition(float x, float y) override;

		void ApplyDamage(int damage);
		void ShowDamage();

		bool IsDieing();

		bool HasTarget();
		void SetTarget(Unit* unit);

		void ActiveSheet() override;

		void StartAttacking()
		{
			attacking = true;
			SwitchStance(Stance::ATTACKING);
		}

		void StopAttacking()
		{
			attacking = false;
			SwitchStance(Stance::STANDING);
		}
};
