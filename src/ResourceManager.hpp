#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

#include<fstream>
#include<vector>
#include<map>
#include<cassert>

#include <SFML/Graphics.hpp>

#include "Collision.hpp"

#include "Utils/Log.hpp"
#include "Utils/FileUtils.hpp"

const float SCALE = 0.8f;

enum class TextureType
{
	GUI,
	SPRITE
};

struct ColorPalette
{
	std::string name;
	sf::Color colors[6];
};

class ResourceManager
{
		std::map<std::string, sf::Texture*> textures;
		std::map<std::string, std::string> texts;
		std::map<std::string, float> variables;

		void InitTexts(const std::string& language);
		sf::Texture* LoadTexture(const std::string& name, TextureType type, const std::string& palette = "");

		void LoadColorPalettes();

	public:
		sf::Font font;
		sf::Font debugFont;

		ResourceManager(const std::string& language);
		~ResourceManager();

		sf::Texture* GetTexture(const std::string& name, TextureType type = TextureType::SPRITE,
								const std::string& palette = "");

		std::string GetTextLine(const std::string& textid);
		sf::String GetSfTextLine(const std::string& textid);

		void InitVariables();
		float GetVariable(const std::string& name);
};

extern ResourceManager* resources;


#endif // FPSCOUNTER_HPP_INCLUDED
