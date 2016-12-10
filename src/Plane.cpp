#include "Plane.hpp"

Plane::Plane(sf::Color planecolor, sf::RenderTarget& window)
{
	width = resources->GetVariable("planebreadth");
	color = planecolor;

	if(text)
	{
		sf::Texture* temp = resources->GetTexture("img/grass");
		temp->setRepeated(true);
		bgtext = new sf::Sprite(*temp);
		bgtext->setPosition(0,window.getSize().y/2-(width/2));
		//bgtext.getTexture()->setRepeated(true);
		bgtext->setTextureRect({ 0, 0, window.getSize().x, width});;
	}
	else
	{
		sf::RectangleShape foo(sf::Vector2f(window.getSize().x, width)); //lel, todelete
		background = foo;

		background.setFillColor(color);

		background.setPosition(0,window.getSize().y/2-(width/2));
	}

	std::cout << "windowsize: x="<< window.getSize().x << " y=" << window.getSize().y << " x/2=" << window.getSize().x/2 << " y/2=" <<window.getSize().y/2<<"\n";

	float gridwidth = resources->GetVariable("gridwidth");
	float temp = window.getSize().x/(resources->GetVariable("columns") + 1);

	//vertical lines
	for(int i = 0; i < resources->GetVariable("columns") + 2; i++)
	{
		sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(width,gridwidth));

		line.setPosition(temp*i,window.getSize().y/2-(width/2));

		line.rotate(90);

		line.setFillColor(sf::Color(0,0,0));

		grid.push_back(line);
	}

	std::cout << "horizontallines: "<<grid.size() << "\n";

	temp = width/(resources->GetVariable("verses") + 1);

	//horizontal lines
	for(int i = 0; i < resources->GetVariable("verses") +2; i++)
	{
		sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(window.getSize().x,gridwidth));

		line.setPosition(0,window.getSize().y/2-(width/2)+ temp*i);

		line.setFillColor(sf::Color(0,0,0));

		grid.push_back(line);
	}

	std::cout << "alllines: "<<grid.size() << "\n\n";

}

Plane::~Plane()
{
	for(auto& it : destructions)
		delete it;
}

void Plane::SwitchGridView()
{
	visiblegrid = !visiblegrid;
}

void Plane::AddDestruction(Destruction* destruction)
{
	destructions.push_back(destruction);
}

void Plane::AddDestruction(const std::string& filename, sf::Vector2f position, int lifetime)
{
	sf::Sprite sprite;
	sprite.setTexture(*resources->GetTexture(filename));
	sprite.setPosition(position);
	sprite.setOrigin(sprite.getGlobalBounds().width/2,sprite.getGlobalBounds().height/2);

	Destruction* dest = new Destruction(sprite,lifetime);

	destructions.push_back(dest);
}

void Plane::UpdateDestructions()
{
	for(auto it = destructions.begin(); it != destructions.end();)
	{
		Destruction* tmp = (*it);
		if( (tmp)->timer.Passed())
		{
			delete (tmp);
			it = destructions.erase(it);
		}
		else
			++it;
	}
}

void Plane::Draw(sf::RenderTarget& window)
{
	window.draw(background);

	window.draw(*bgtext);

	for(auto& it : destructions)
		window.draw(it->sprite);

	if(visiblegrid)
		for(auto& it : grid)
			window.draw(it);
}

float Plane::GetStartY()
{
	if(text)
		return bgtext->getPosition().y;

	return background.getPosition().y;
}

float Plane::GetEndY()
{
	return GetStartY()+width;
}
