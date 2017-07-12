#pragma once

#include "defines.h"
#include "Singleton.h"
#include "IUpdateDraw.h"
/*
* 引擎主要负责各种Manger的载入和初始化
比方说： SenceManager TextureManger  
*/
class Engine : public Singleton<Engine>
{
public:
	friend Singleton<Engine>;

	~Engine();
	void Init();
	void Update(double dt);
	void Draw();
	double GetDeltaTime() { return m_DeltaTime; }
private:
	Engine();
	double m_DeltaTime;
	IUpdateDraw * mSence;

};