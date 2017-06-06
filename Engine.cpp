#include "Engine.h"	
#include "Texture.h"
#include "SpriteBatch.h"
#include "CubeBatch.h"
#include "InputManager.h"
#include "Projects/TestSence.h"

Engine::~Engine()
{

}


Engine::Engine()
: Singleton<Engine>()
{

}


TestSence* mSence;

void Engine::Init()
{
    mSence = new TestSence();

    glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    SpriteBatch::GetInstance()->Init();
    CubeBatch::GetInstance()->Init();
    
    InputManager::GetInstance()->SetKeyCallback();
    InputManager::GetInstance()->SetScrollCallback();
    InputManager::GetInstance()->SetMouseCallback();
}

void Engine::Update()
{
    mSence->Update();
}

void Engine::Draw()
{ 
    mSence->Draw();
    CubeBatch::GetInstance()->Flush();
    SpriteBatch::GetInstance()->Flush();
}