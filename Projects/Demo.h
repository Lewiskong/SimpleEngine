#pragma once

#include "IUpdateDraw.h"
#include "InputManager.h"

#define PI 3.1415926
#define DegreeToRadian(d) (d*PI/180.0f)
#define RadianToDegree(r) (r*180.0f/PI)


class Demo :public IUpdateDraw ,public MouseButtonCallback
{
public:

	Demo();
	~Demo();
	void Update() override;
	void Draw() override;
	
	void OnClick(int button, int action, int mods) override;
};