#include "Game.h"	


Game::Game(int w,int h,std::string title)
{
	mResWidth =  w;
	mResHeight = h;
	mTitle = title;

	/*
	各种初始化 
	*/
	
}

Game::~Game()
{

}


void Game::Start()
{
	Engine::GetInstance()->Init();
 
}

void  Game::Update()
{
	Engine::GetInstance()->Update();
}

void  Game::Draw()
{

	Engine::GetInstance()->Draw();

}

void  Game::End()
{

}