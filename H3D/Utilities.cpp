#include "Utilities.hpp"
#include <time.h>
/////////////////////////////////////////////////////////////////
// Implementation of Logger
/////////////////////////////////////////////////////////////////
h3d::__Logger::__Logger() {}
h3d::__Logger::~__Logger() {}
/////////////////////////////////////////////////////////////////
std::string h3d::__Logger::getCurrentTime()
{
	std::string currTime;
	time_t now = time(0);
	currTime.assign(ctime(&now));
	currTime.erase(std::end(currTime));
	return currTime;
}
/////////////////////////////////////////////////////////////////
// Log Functions
template<typename... Args>
	void h3d::__Logger::error(char* msg,Args... args)
{
	if (m_currentLogType == LogTypes::CONSOLE)
	{

	}
	else if (m_currentLogType == LogTypes::FILE)
	{
		std::lock_guard<std::mutex> lock(m_fileMutex);
		fprintf(m_logFile, msg,ap);
	}
}
/////////////////////////////////////////////////////////////////