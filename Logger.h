#pragma once
#include "Singleton.h"	

class Logger final : public Singleton<Logger>
{
public:
	static void Error(std::string msg) { std::cout<<"Error:"<<msg<<std::endl; }
	static void Warning(std::string msg) { std::cout<<"Warning:"<<msg<<std::endl; }
private:
	Logger() : Singleton<Logger>() {}
	~Logger();
	
};