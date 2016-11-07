#ifndef FILEUTILS_HPP_INCLUDED
#define FILEUTILS_HPP_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <deque>

void ReadFile(const char* filename, std::string& buffer);


void Convert(std::string text, int& param);
void Convert(std::string text, bool& param);
void Convert(std::string text, float& param);
void Convert(std::string text, std::string& param);


template<typename T>
void FillArgs(std::deque<std::string>& texts, T& arg)
{
	if( !texts.empty())
	{
		Convert(texts.front(), arg);
		texts.pop_front();
	}
	else
		Convert("", arg);
}

template<typename T1, typename ...Ts>
void FillArgs(std::deque<std::string>& texts, T1& arg, Ts& ... args)
{
	FillArgs(texts, arg);
	FillArgs(texts, args...);
}

template<typename ...Ts>
bool ReadRowFromCSV(std::fstream& file, Ts& ... args)
{
	std::string line;
	std::deque<std::string> texts;

	getline(file, line);

	if(line.empty() || line == "\n")
		return false;

	std::size_t prev = 0, pos;
	while ((pos = line.find_first_of(";", prev)) != std::string::npos)
	{
		if (pos > prev)
			texts.push_back(line.substr(prev, pos-prev));
		else
			texts.push_back("0");
		prev = pos+1;
	}
	if (prev < line.length())
		texts.push_back(line.substr(prev, std::string::npos));

	FillArgs(texts, args...);

	return true;
}

#endif // FILEUTILS_HPP_INCLUDED
