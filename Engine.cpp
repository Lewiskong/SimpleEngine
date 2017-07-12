#include "Engine.h"	
#include "Texture.h"
#include "SpriteBatch.h"
#include "CubeBatch.h"
#include "InputManager.h"
#include "Projects/TestSence.h"
#include "Projects/Demo.h"

Engine::~Engine()
{

}


Engine::Engine()
: Singleton<Engine>()
{

}




IUpdateDraw * mSence;

void Engine::Init()
{
	
	mSence = new TestSence();
	//mSence = new Demo();
    
    InputManager::GetInstance()->SetKeyCallback();
    InputManager::GetInstance()->SetScrollCallback();
    InputManager::GetInstance()->SetMouseCallback();

    
}

void Engine::Update(double dt)
{
    m_DeltaTime = dt;
    mSence->Update();

}

void Engine::Draw()
{ 
    mSence->Draw();

  
}