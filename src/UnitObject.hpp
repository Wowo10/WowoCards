#ifndef UNITOBJECT_HPP_INCLUDED
#define UNITOBJECT_HPP_INCLUDED

#include "Object.hpp"

class UnitObject : public Object
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

		bool IsDieing();

		void ActiveSheet() override;
};

#endif UNITOBJECT_HPP_INCLUDED
