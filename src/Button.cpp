#include "Button.hpp"

Button::Button(sf::Vector2f pos, std::string graphics, std::string graphics_hover) : Object(ObjectType::BUTTON)
{

	SetPosition(pos.x,pos.y);
	SetSprite(graphics);
	hover_sprite.setTexture( *resources->GetTexture(graphics_hover, TextureType::SPRITE));

	auto rect = hover_sprite.getLocalBounds();
	hover_sprite.setOrigin(rect.width / 2.0f, rect.height / 2.0f);
	hover_sprite.setPosition(pos.x,pos.y);
}

void Button::Update()
{

}

void Button::Render(sf::RenderTarget& window)
{
	if (hoverd)
		window.draw(hover_sprite);
	else
		window.draw(sprite);
}

void Button::OnClick()
{
	std::cout<<"KLIK"<<std::endl;
}

void Button::OnHover()
{
	if(!hoverd)
	{
		hoverd=true;
	}
}

void Button::OnHoverExit()
{
	if(hoverd)
	{
		hoverd=false;
	}
}
