#ifndef POLARVECTOR_HPP
#define POLARVECTOR_HPP

///Polar Vector class
#include <SFML/System/Vector2.hpp>

///The class uses radians as angles, where r is the radius and t is the angle.

class PolarVector
{
	public:
		float r;
		float t;

		PolarVector();
		PolarVector(float radius, float angle);

		sf::Vector2f TurnToRectangular() const;
	private:
		static const float EPSILON;

		friend bool operator ==(const PolarVector& left, const PolarVector& right);
};

PolarVector TurnToPolar(const sf::Vector2f& point);

bool operator ==(const PolarVector& left, const PolarVector& right);

bool operator !=(const PolarVector& left, const PolarVector& right);

#endif // POLARVECTOR_HPP
