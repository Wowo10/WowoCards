#include "InstancedSprite.hpp"
#include "PolarVector.hpp"
#include <cmath>

InstancedSprite::InstancedSprite(const unsigned objamount)
	: amount(objamount)
{
	vertexholder.reserve(amount*4);
	positionholder.reserve(amount);
	scaleholder.reserve(amount);
	angleholder.reserve(amount);

	for(unsigned i = 0; i < amount; ++i)
	{
		for(unsigned j = 0; j < 4; ++j)
		{ vertexholder.push_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color(255, 255, 255, 255))); }

		positionholder.push_back(sf::Vector2f(0, 0));
		scaleholder.push_back(sf::Vector2f(1.f, 1.f));
		angleholder.push_back(0.f);
		texrectholder.push_back(sf::IntRect(0, 0, 0, 0));
	}
}

InstancedSprite::InstancedSprite(sf::Texture& T, const unsigned objamount)
	: amount(objamount), texture(&T)
{
	vertexholder.reserve(amount * 4);
	positionholder.reserve(amount);
	scaleholder.reserve(amount);
	angleholder.reserve(amount);

	for(unsigned i = 0; i < amount; ++i)
	{
		for(unsigned j = 0; j < 4; ++j)
		{ vertexholder.push_back(sf::Vertex(sf::Vector2f(0.f, 0.f), sf::Color(255, 255, 255, 255))); }

		positionholder.push_back(sf::Vector2f(0, 0));
		scaleholder.push_back(sf::Vector2f(1.f, 1.f));
		angleholder.push_back(0.f);
		setTextureRect(i, sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y));
	}
}

InstancedSprite::~InstancedSprite() {}

InstancedSprite::InstancedSprite(const InstancedSprite& other)
{
	amount = other.amount;
	texture = other.texture;
	vertexholder = other.vertexholder;
	angleholder = other.angleholder;
	positionholder = other.positionholder;
	scaleholder = other.scaleholder;
	texrectholder = other.texrectholder;
	hastexture = other. hastexture;
}

InstancedSprite& InstancedSprite::operator=(const InstancedSprite& rhs)
{
	if (this == &rhs) return *this; // handle self assignment
	amount = rhs.amount;
	texture = rhs.texture;
	vertexholder = rhs.vertexholder;
	angleholder = rhs.angleholder;
	positionholder = rhs.positionholder;
	scaleholder = rhs.scaleholder;
	texrectholder = rhs.texrectholder;
	hastexture = rhs. hastexture;
	return *this;
}

void InstancedSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = texture;
	target.draw(&vertexholder[0], static_cast<unsigned>(vertexholder.size()), sf::Quads, states);
}

void InstancedSprite::setTexture(sf::Texture& T)
{
	texture = &T;
	setGlobalTextureRect(sf::IntRect(0, 0, texture->getSize().x, texture->getSize().y) );
}

void InstancedSprite::setTextureRect(const unsigned index, const sf::IntRect& IR)
{
	texrectholder[index] = IR;
	updateTexCoords(index);
	updateVertexCoords(index, false);
}

void InstancedSprite::setGlobalTextureRect(const sf::IntRect& IR)
{
	for(unsigned i = 0; i < amount; ++i)
	{ setTextureRect(i, IR); }
}

void InstancedSprite::updateTexCoords(const unsigned index)
{
	float left = static_cast<float>(texrectholder[index].left);
	float right = left + texrectholder[index].width;
	float top = static_cast<float>(texrectholder[index].top);
	float bottom = top + texrectholder[index].height;

	unsigned I = index * 4;

	vertexholder[I++].texCoords = sf::Vector2f(left, top);
	vertexholder[I++].texCoords = sf::Vector2f(left, bottom);
	vertexholder[I++].texCoords = sf::Vector2f(right, bottom);
	vertexholder[I].texCoords = sf::Vector2f(right, top);
}

void InstancedSprite::updateVertexCoords(const unsigned index, const bool Reset)
{
	sf::Vector2u S;
	S.x = texrectholder[index].width * scaleholder[index].x;
	S.y = texrectholder[index].height * scaleholder[index].y;

	unsigned I = index * 4;

	vertexholder[I++].position = sf::Vector2f(0, 0);
	vertexholder[I++].position = sf::Vector2f(0, S.y);
	vertexholder[I++].position = sf::Vector2f(S.x, S.y);
	vertexholder[I].position = sf::Vector2f(S.x, 0);

	if(Reset)
	{
		positionholder[index].x = 0.f;
		positionholder[index].y = 0.f;
	}
	else
	{ move(index, positionholder[index]); }
}

void InstancedSprite::move(const unsigned index, const float x, const float y)
{
	unsigned limit = (index * 4) + 4;
	for(unsigned I = index * 4; I < limit; ++I)
	{
		vertexholder[I].position.x += x;
		vertexholder[I].position.y += y;
	}
	positionholder[index].x += x;
	positionholder[index].y += y;
}

void InstancedSprite::move(const unsigned index, const sf::Vector2f& V)
{ move(index, V.x, V.y); }

void InstancedSprite::globalMove(const sf::Vector2f& V)
{
	for(unsigned i = 0; i < amount; ++i)
	{ move(i, V.x, V.y); }
}

void InstancedSprite::setPosition(const unsigned index, const float x, const float y)
{
	move(index, -(positionholder[index].x), -(positionholder[index].y));
	move(index, x, y);
}

void InstancedSprite::setPosition(const unsigned index, const sf::Vector2f& V)
{ setPosition(index, V.x, V.y); }

void InstancedSprite::setGlobalPosition(const sf::Vector2f& V)
{
	for(unsigned i = 0; i < amount; ++i)
	{ setPosition(i, V); }
}

void InstancedSprite::setRotation(const unsigned index, const float ang)
{
	float ang_t = ang;
	angleholder[index] = fmod(ang, 360.f);
	PolarVector P = TurnToPolar(positionholder[index]); P.t = ang_t;
	setPosition(index, P.TurnToRectangular() );
}

void InstancedSprite::setGlobalRotation(const float ang)
{
	for(unsigned i = 0; i < amount; ++i)
	{ setRotation(i, ang); }
}

void InstancedSprite::rotate(const unsigned index, const float ang)
{ setRotation(index, angleholder[index] + ang); }

void InstancedSprite::globalRotate(const float ang)
{
	for(unsigned i = 0; i < amount; ++i)
	{ rotate(i, ang); }
}

void InstancedSprite::rotateAroundSelf(const unsigned index, const float ang)
{
	float ang_t = ang * TORAD;
	sf::Vector2f Tmp = positionholder[index];
	sf::Vector2f Off(-(texrectholder[index].width/2.f), -(texrectholder[index].height/2.f));

	setPosition(index, Off);
	unsigned limit = (index * 4) + 4;
	for(unsigned i = index * 4; i < limit; ++i)
	{
		PolarVector P(TurnToPolar(vertexholder[i].position));
		P.t += ang_t;
		vertexholder[i].position = P.TurnToRectangular();
	}
	move(index, Tmp - Off);
}

void InstancedSprite::globalRotateAroundSelf(const float ang)
{
	for(unsigned i = 0; i < amount; ++i)
	{ rotateAroundSelf(i, ang); }
}

void InstancedSprite::resetSelfRotation(const unsigned index)
{ updateVertexCoords(index, false); }

void InstancedSprite::resetGlobalSelfRotation()
{
	for(unsigned i = 0; i < amount; ++i)
	{ updateVertexCoords(i, false); }
}

void InstancedSprite::setScale(const unsigned index, const float x, const float y)
{
	scaleholder[index].x = x;
	scaleholder[index].y = y;
	for(unsigned i = index * 4; i < (index * 4) + 4; ++i)
	{
		vertexholder[i].position.x *= x;
		vertexholder[i].position.y *= y;
	}
}

void InstancedSprite::setScale(const unsigned index, const sf::Vector2f& V)
{ setScale(index, V.x, V.y); }

void InstancedSprite::setGlobalScale(const sf::Vector2f& V)
{
	for(unsigned i = 0; i < amount; ++i)
	{ setScale(i, V); }
}

void InstancedSprite::setAlpha(const float alpha)
{
	for(unsigned i = 0; i < amount; ++i)
	{
		vertexholder[i].color.a = 255 * alpha;
	}
}

sf::Vector2f InstancedSprite::getPosition(const unsigned index) const
{ return positionholder[index]; }

sf::Vector2f InstancedSprite::getScale(const unsigned index) const
{ return scaleholder[index]; }

float InstancedSprite::getRotation(const unsigned index) const
{ return angleholder[index]; }
