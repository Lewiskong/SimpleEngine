#include "TestSence.h"
#include "../Engine.h"
#include "Texture.h"
#include "SpriteBatch.h"
#include "CubeBatch.h"
#include "InputManager.h"
#include "../Objects/MapObject.h"

MapObject* pMapObject;

TestSence::TestSence()
{
   // pMapObject = new MapObject("Map");
	pMapObject = new MapObject();
}

TestSence::~TestSence()
{

}

void TestSence::Update()
{
	  pMapObject -> Update();
 
}

void TestSence::Draw()
{
	pMapObject->Draw();
}
	
