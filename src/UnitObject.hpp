#ifndef UNITOBJECT_HPP_INCLUDED
#define UNITOBJECT_HPP_INCLUDED

#include "AnimatedObject.hpp"

class UnitObject : public AnimatedObject
{
	protected:
		int health, maxhealth;

		sf::Text TID;

		//sf::Sprite sprite;
	public:
		UnitObject(const std::string& name, Course direction, ObjectType type);
		~UnitObject();

		static int ID;
		int id;

		void Update(float frame_time) override;
		virtual void Render(sf::RenderTarget& window, bool showids);

		void SetPosition(float x, float y) override;

		void ApplyDamage(int damage);
		void ShowDamage();

		void SwitchStance(Stance stance) override;

		bool IsDieing();

		void ActiveSheet() override;
};

#endif UNITOBJECT_HPP_INCLUDED
