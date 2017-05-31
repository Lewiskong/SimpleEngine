#pragma once
#include "defines.h"
#include "Game.h"


/*用于控制Game 负责Game的Init Update Draw*/
class Window
{
public:
	Window(int w,int h);
	~Window();
	
	void Show();

private:
	GLFWwindow *p_Window;
	Game* p_Game;
};