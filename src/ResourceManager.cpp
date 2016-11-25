#include "ResourceManager.hpp"

ResourceManager* resources;

ResourceManager::ResourceManager(const std::string& language)
{
	if (!font.loadFromFile("Data/font/Furore.otf"))
		Log("Cannot load font file!\n");
	if (!debugFont.loadFromFile("Data/font/Furore.otf"))
		Log("Cannot load debug font file!\n");

	InitTexts(language);
	InitVariables();
}

ResourceManager::~ResourceManager()
{
	for(auto it : textures)
	{
		delete it.second;
	}

	textures.clear();
}

sf::Texture* ResourceManager::LoadTexture(const std::string& name, TextureType type, const std::string& palette)
{
	sf::Texture* texture = new sf::Texture();

	std::string filename = "Data/"+name+".png";

	if(type == TextureType::SPRITE)
	{
		if (!Collision::CreateTextureAndBitmask(*texture, filename))
		{
			Log("Cannot load texture: ", filename, "\n");
		}

		texture->setSmooth(true);
	}
	else
	{
		if (!texture->loadFromFile(filename))
		{
			Log("Cannot load texture: ", filename, "\n");
		}

		texture->setSmooth(true);
		texture->setRepeated(true);
	}

	textures[name] = texture;

	return texture;
}

sf::Texture* ResourceManager::GetTexture(const std::string& name, TextureType type,
		const std::string& palette)
{
	std::string texname = name + palette;
	auto it = textures.find(texname);
	if(it == textures.end())
	{
		return LoadTexture(name, type, palette);
	}

	return (*it).second;
}

void ResourceManager::InitTexts(const std::string& language)
{
	texts.clear();
	std::fstream textfile;
	textfile.open("Data/texts.csv", std::ios::in);

	std::string textid, pl, en, ru, ge;

	while(textfile.good())
	{
		if(ReadRowFromCSV(textfile, textid, pl, en, ru, ge))
		{
			if(language=="PL")
				texts[textid] = pl;
			else if(language=="EN")
				texts[textid] = en;
			else if(language=="RU")
				texts[textid] = ru;
			else if(language=="GE")
				texts[textid] = ge;
			else
			{
				Log("Error, not supported language\n");
				return;
			}
		}
	}
}

void ResourceManager::InitVariables()
{
	variables.clear();
	std::fstream textfile;
	textfile.open("Data/variables.csv", std::ios::in);

	std::string name, value, temp;

	if(textfile.good())
	{
		getline(textfile, name);

		while(textfile.good())
		{
			if(ReadRowFromCSV(textfile, name, value, temp))
			{
				variables[name] = std::stof(value);
			}
		}
	}
	else
		Log("Cannot open variables.csv file!\n");
}


std::string ResourceManager::GetTextLine(const std::string& textid)
{
	if(texts.find(textid) != texts.end() )
	{
		return texts.find(textid)->second;
	}
	else
	{
		Log("Error, text line with id: ", textid, "not found\n");
		return "ERROR";
	}
}

sf::String ResourceManager::GetSfTextLine(const std::string& textid)
{
	if(texts.find(textid) != texts.end() )
	{
		std::string in = texts.find(textid)->second;
		sf::String out;
		std::basic_string < sf::Uint32 > tmp;
		sf::Utf8::toUtf32( in.begin(), in.end(), std::back_inserter(tmp));
		out = tmp;

		return out;
	}
	else
	{
		Log("Error, text line with id: ", textid, "not found\n");
		return "ERROR";
	}
}

float ResourceManager::GetVariable(const std::string& name)
{
	if(variables.find(name) != variables.end() )
	{
		return variables.find(name)->second;
	}
	else
	{
		Log("Error, variable with id: ", name, "not found\n");
		std::cout << "Cannot find variable with id: " << name << "\n";
		return 1;
	}
}
