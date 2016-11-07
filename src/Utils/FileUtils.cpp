#include "FileUtils.hpp"

void ReadFile(const char* filename, std::string& buffer)
{
	std::ifstream f(filename);
	if (!f.is_open())
		return;

	f.seekg(0, std::ios::end);
	buffer.reserve(f.tellg());
	f.seekg(0, std::ios::beg);

	buffer.assign( (std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()) );

	f.close();
}

void Convert(std::string text, int& param)
{
	param = std::stoi(text);
}

void Convert(std::string text, bool& param)
{
	param = std::stoi(text);
}

void Convert(std::string text, float& param)
{
	param = std::stof(text);
}

void Convert(std::string text, std::string& param)
{
	param = text;
}
