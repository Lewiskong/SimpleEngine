#include "defines.h"

//包含Window 创建出来一个window
#include "Window.h"
#include "global.h"
/*
Program负责window的外部交互 例如创建窗口 移动窗口 主要负责将操作系统上的外部操作转换成游戏里面的内部操作
*/
int main()
{
	/*根据配置创建出来一个窗口，窗口的作用是初始化游戏 以及结束游戏 这里相当于说创建一个游戏窗口*/
	Window* p_Window =new  Window(SCREEN_WIDTH,SCREEN_HEIGHT);
	p_Window->Show();
	return 0;
}