#pragma once

#include "defines.h"
#include "Shader.h"
#include "Texture.h"
#include "Environment.h"

/*
* 引擎主要负责各种Manger的载入和初始化
比方说： SenceManager TextureManger  
*/
class Engine
{
public:
	~Engine();
	static Engine* GetInstance();
	void Init();
	void Update();
	void Draw();

private:
	static Engine *p_Engine;
	Engine();

};