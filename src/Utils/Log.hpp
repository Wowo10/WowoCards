#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED

#include <fstream>
#include <iostream>

#include<sstream>

#define PI 3.141592

extern std::fstream log_file;

template<typename T>
void Log(T arg)
{
	log_file<<arg;
	log_file.flush();
}

template<typename T1, typename ...Ts>
void Log(T1 arg, Ts... args)
{
	Log(arg);
	Log(args...);
}

void InitLog();
void CloseLog();

template <typename T>
std::string to_string(T value)
{
	//create an output string stream
	std::ostringstream os ;

	//throw the value into the string stream
	os << value ;

	//convert the string stream into a string and return
	return os.str() ;
}


#endif // LOG_HPP_INCLUDED
