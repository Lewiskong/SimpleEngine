#pragma once

#include "defines.h"

class Environment
{
public:
	Environment();
	~Environment();
	
	static std::string GetPath()
	{
		return "/Users/oceancx/OpenGL";
	}

	static std::string GetAbsPath(std::string localPath)
	{
		return GetPath()+"/"+localPath;
	}
};