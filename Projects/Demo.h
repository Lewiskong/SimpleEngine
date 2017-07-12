#pragma once

#include "IUpdateDraw.h"
class Demo :public IUpdateDraw
{
public:
	Demo();
	~Demo();
	void Update() override;
	void Draw() override;
	
};