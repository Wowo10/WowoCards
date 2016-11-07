#include<fstream>

#include "Utils/Log.hpp"
#include "Options.hpp"

void Options::LoadFromFile()
{
	std::fstream text_file;
	std::string line;
	text_file.open( "Data/settings.ini", std::ios::in);
	if( text_file.good() == false )
		Log("Cannot open settings file!\n");

	while(text_file.good())
	{
		getline(text_file, line);
		sets.push_back(line);
	}
	text_file.close();
	resolution_x = std::stoi(sets[10]);
	resolution_y = std::stoi(sets[11]);
	fullscreen = std::stoi(sets[13]);
	multisampling = std::stoi(sets[15]);
	vsync = std::stoi(sets[17]);
	volumeMusic = std::stoi(sets[19]);
	volumeSound = std::stoi(sets[21]);
	language = sets[23];

	userPath = sets[27];

	first_run = std::stoi(sets[8]);
}

void Options::SaveToFile()
{
	std::fstream settings_file;
	settings_file.open( "Data/settings.ini", std::ios::out );//| ios::trunc);
	settings_file << sets[0];
	for(unsigned int i = 1; i < sets.size(); i++)
	{
		settings_file << "\n" << sets[i];
	}
	settings_file.close();
}
