#include "Engine.h"	
#include "Texture.h"
#include "SpriteBatch.h"
#include "CubeBatch.h"
#include "InputManager.h"
#include "Projects/TestSence.h"
#include "Projects/Demo.h"

Engine::~Engine()
{
	if (mSence != nullptr)
	{
		delete mSence;
		mSence = nullptr;
	}
}


Engine::Engine()
: Singleton<Engine>()
{
	//mSence = new TestSence();
	mSence = new Demo();
}

void Engine::Init()
{
	
	
    InputManager::GetInstance()->SetKeyCallback();
    InputManager::GetInstance()->SetScrollCallback();
    InputManager::GetInstance()->SetMouseCallback();
	InputManager::GetInstance()->SetMouseButtonCallback();
    
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