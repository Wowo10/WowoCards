#ifndef SPELL_HPP_INCLUDED
#define SPELL_HPP_INCLUDED

#include "AnimatedObject.hpp"

enum SpellType
{
	DAMAGE = 0,
	HEAL,
	BUFF
};

enum CastType
{
	SINGLE = 0,
	LINE,
	AOE
};

enum Target
{
	UNITS = 0,
	CHAMPIONS,
	STRUCTURES,
	ALL
};

class Spell : public AnimatedObject
{
	Spell();
};

#endif //SPELL_HPP_INCLUDED
