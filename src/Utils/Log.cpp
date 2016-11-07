#include "Log.hpp"

std::fstream log_file;

void InitLog()
{
	log_file.open("User/log.txt", std::ios::app|std::ios::out);
}

void CloseLog()
{
	Log("close log\n");
	log_file.close();
}
