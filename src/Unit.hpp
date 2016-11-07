#include "Object.hpp"

class Unit : public Object
{
		int health, maxhealth;
		int damage, range;

		sf::Vector2f destination;

		//sf::Sprite sprite;
	public:
		Unit(const std::string& name,Course direction, int posY);
		~Unit();

		bool attacking;

		void Update(float frame_time); //override;
		void Render(sf::RenderTarget& window) override;

		void SetPosition(float x, float y) override;

		void ApplyDamage(int damage);
		void ShowDamage();

		void MoveTo(sf::Vector2f destination);

		void StartAttacking()
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
