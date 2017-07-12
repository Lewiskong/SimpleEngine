#pragma once
#include "defines.h"
#include "Game.h"
#include "Singleton.h"


/*用于控制Game 负责Game的Init Update Draw*/
class Window : public Singleton<Engine>
{
public:
	friend Singleton<Engine>;

	Window(int w,int h);
	~Window();
	
	void Show();
	GLFWwindow* GetGLFWwindow();

private:
	GLFWwindow *p_Window;
	Game* p_Game;
};