#ifndef ALTSPRITEHOLDER_HPP
#define ALTSPRITEHOLDER_HPP

#include <vector>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Log.hpp"

const float TORAD = PI/180.0f;
const float TODEG = 180.0f/PI;


class InstancedSprite : public sf::Drawable
{
	public:
		InstancedSprite(const unsigned objamount);
		InstancedSprite(sf::Texture& T, const unsigned objamount);
		~InstancedSprite();

		InstancedSprite(const InstancedSprite& other);
		InstancedSprite& operator=(const InstancedSprite& other);

		void setTexture(sf::Texture& T);

		void setTextureRect(const unsigned index, const sf::IntRect& IR);
		void setGlobalTextureRect(const sf::IntRect& IR);

		void move(const unsigned index, const sf::Vector2f& V);
		void move(const unsigned index, const float x, const float y);
		void globalMove(const sf::Vector2f& V);

		void setPosition(const unsigned index, const sf::Vector2f& V);
		void setPosition(const unsigned index, const float x, const float y);
		void setGlobalPosition(const sf::Vector2f& V);

		void setRotation(const unsigned index, const float ang);
		void setGlobalRotation(const float ang);

		void rotate(const unsigned index, const float ang);
		void globalRotate(const float ang);

		void rotateAroundSelf(const unsigned index, const float ang);
		void globalRotateAroundSelf(const float ang);

		void resetSelfRotation(const unsigned index);
		void resetGlobalSelfRotation();

		void scale(const unsigned index, const sf::Vector2f& V);
		void globalScale(const sf::Vector2f& V);

		void setScale(const unsigned index, const float x, const float y);
		void setScale(const unsigned index, const sf::Vector2f& V);
		void setGlobalScale(const sf::Vector2f& V);

		sf::Vector2f getPosition(const unsigned index) const;
		sf::Vector2f getScale(const unsigned index) const;
		float getRotation(const unsigned index) const;

		void setAlpha(const float alpha);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		unsigned amount;

		sf::Texture* texture;

		std::vector<sf::Vertex> vertexholder;

		std::vector<float> angleholder;
		std::vector<sf::Vector2f> positionholder;
		std::vector<sf::Vector2f> scaleholder;
		std::vector<sf::IntRect> texrectholder;

		bool hastexture;

		void updateTexCoords(const unsigned index);
		void updateVertexCoords(const unsigned index, const bool Reset = true);

		void updateAngleRanges(const unsigned index);
};

#endif // ALTSPRITEHOLDER_HPP
