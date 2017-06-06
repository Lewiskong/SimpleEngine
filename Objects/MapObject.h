#pragma once

#include "Object.h"

class MapObject : public Object
{
public:
	MapObject();
	MapObject(const std::string & name);
	~MapObject();

	void Reset();
	void Initialize();
	void AfterInitialized();
	void Update();
	void Draw();
	
};