#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "Object.hpp"

class Button : public Object
{
		sf::Sprite hover_sprite;

	public:

		Button(sf::Vector2f pos, std::string graphics, std::string graphics_hover);
		void Update();
		void Render(sf::RenderTarget& window);
		void OnClick();
		void OnHover();
		void OnHoverExit();
		bool clicked = false;
		bool hoverd = false;

};

#endif
