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


TestSence* mSence;
Demo* mDemo;

void Engine::Init()
{
 //   mSence = new TestSence();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    // SpriteBatch::GetInstance()->Init();
    // CubeBatch::GetInstance()->Init();
    
    InputManager::GetInstance()->SetKeyCallback();
    InputManager::GetInstance()->SetScrollCallback();
    InputManager::GetInstance()->SetMouseCallback();


    mDemo  = new Demo();
}

void Engine::Update(double dt)
{
    m_DeltaTime = dt;
    //mSence->Update();
    mDemo->Update();
}

void Engine::Draw()
{ 
    //mSence->Draw();
    mDemo->Draw();
    // CubeBatch::GetInstance()->Flush();
    // SpriteBatch::GetInstance()->Flush();
}