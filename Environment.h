#pragma once

#include "defines.h"

#define WORK_DIR "/Users/oceancx/SimpleEngine"
class Environment
{
public:
	Environment();
	~Environment();
	
	static std::string GetPath()
	{
		return WORK_DIR;
	}

	static std::string GetAbsPath(std::string localPath)
	{
		return GetPath()+"/"+localPath;
	}
};