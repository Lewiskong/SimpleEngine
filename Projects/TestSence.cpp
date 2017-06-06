#include "TestSence.h"
#include "../Engine.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "CubeBatch.h"
#include "InputManager.h"
#include "../Objects/MapObject.h"


glm::vec3 cubePositions[] = 
{
	glm::vec3(0.0f, 0.0f, 0.0f), 
	glm::vec3(2.0f, 5.0f, -15.0f), 
	glm::vec3(-1.5f, -2.2f, -2.5f),  
	glm::vec3(-3.8f, -2.0f, -12.3f),  
	glm::vec3(2.4f, -0.4f, -3.5f),  
	glm::vec3(-1.7f, 3.0f, -7.5f),  
	glm::vec3(1.3f, -2.0f, -2.5f),  
	glm::vec3(1.5f, 2.0f, -2.5f), 
	glm::vec3(1.5f, 0.2f, -1.5f), 
	glm::vec3(-1.3f, 1.0f, -1.5f)  
};

Texture* p_Texture;
int tw,th;

glm::mat4 view;
glm::mat4 projection = glm::perspective(45.0f, 800.0f/600.0f, 0.1f, 1000.0f);;   

glm::vec3 pos = glm::vec3(0,0,3);
glm::vec3 front = glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);


MapObject* pMapObject;
TestSence::TestSence()
{
   // pMapObject = new MapObject("Map");
	pMapObject = new MapObject();

	p_Texture = new Texture("/Users/oceancx/SimpleEngine/Resource/Assets/bizhi.jpg");
	tw = p_Texture->GetWidth();
	th = p_Texture->GetHeight();
}

TestSence::~TestSence()
{

}

void TestSence::Update()
{
	for(int i=0;i<1;i++)
	{
		SpriteInfo* info = new SpriteInfo();
		info->Pos.x = 100+i*10;
		info->Pos.y = -200+i*10;
		info->Size.x = tw;
		info->Size.y = th;
		info->Alpha = 0.9f;
		info->TextureID = p_Texture->GetTextureID();

		SpriteBatch::GetInstance()->AddSprite(info);
	}


	if(InputManager::GetInstance()->IsKeyDown(GLFW_KEY_W))
	{
		pos.y-=0.1F;
	}


	if(InputManager::GetInstance()->IsKeyDown(GLFW_KEY_A))
	{
		pos.x+=0.1F;
	}


	if(InputManager::GetInstance()->IsKeyDown(GLFW_KEY_S))
	{
		pos.y+=0.1F;
	}


	if(InputManager::GetInstance()->IsKeyDown(GLFW_KEY_D))
	{
		pos.x-=0.1F;
	}

	view = glm::lookAt(pos, pos + front, up);

	for(int i=0;i<10;i++)
	{
		glm::mat4 model;
        //model = glm::scale(model,glm::vec3(0.5,0.5,0.5));            
		model = glm::translate(model,cubePositions[i]);            
		GLfloat angle = 20.0f * i; 
		model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

		CubeInfo* info = new CubeInfo();
		info->Model =glm::mat4(model);
		info->View =glm::mat4(view);
		info->Projection = glm::mat4(projection);
		info->FillColor = glm::vec4(0,1,1,1);
		info->TextureID = p_Texture->GetTextureID();
		CubeBatch::GetInstance()->AddCube(info);
	}


	pMapObject -> Update();

}

void TestSence::Draw()
{
	pMapObject->Draw();
}

