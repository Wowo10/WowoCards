#ifndef OPTIONS_HPP_INCLUDED
#define OPTIONS_HPP_INCLUDED

#include<string>
#include<vector>


struct Options
{
	float resolution_x, resolution_y;

	bool vsync;
	bool first_run;

	bool fullscreen;
	short int multisampling;

	short int volumeMusic;
	short int volumeSound;

	std::string language;
	std::string userPath;

	std::vector<std::string> sets;

	void LoadFromFile();
	void SaveToFile();
};

#endif // OPTIONS_HPP_INCLUDED
