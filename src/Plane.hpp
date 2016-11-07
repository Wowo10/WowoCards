#include <SFML/Graphics.hpp>
#include <vector>
#include "GameTimer.hpp"
#include "ResourceManager.hpp"

struct Destruction
{
	sf::Sprite sprite;
	GameTimer timer;

	Destruction(sf::Sprite destructionsprite, int lifetime)
	{
		sprite = destructionsprite;
		timer.AddDelta(lifetime);
	}
};

class Plane
{

		sf::Color color;
		bool visiblegrid = true;
		sf::RectangleShape background;

		std::vector<sf::RectangleShape> grid;
		std::vector<Destruction*> destructions;

	public:
		Plane(sf::Color planecolor, sf::RenderTarget& window);
		~Plane();

				float width;

		void SwitchGridView();
		void AddDestruction(Destruction* destruction);
		void AddDestruction(const std::string& filename, sf::Vector2f position, int lifetime);
		void UpdateDestructions();
		void Draw(sf::RenderTarget& window);

		float GetStartY();
		float GetEndY();
};
