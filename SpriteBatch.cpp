#include "SpriteBatch.h"
#include "Environment.h"

SpriteBatch::SpriteBatch()
	:Singleton<SpriteBatch>()
	,m_SpriteQueue()
	,m_ShaderPtr(nullptr)
{

}

SpriteBatch::~SpriteBatch(void)
{
	delete m_ShaderPtr;
}

void SpriteBatch::Init()
{
	std::string vPath =  Environment::GetAbsPath("Shader/MvpVertexShader");
	std::string fPath =  Environment::GetAbsPath("Shader/MvpFragmentShader");

	m_ShaderPtr = new Shader(vPath,fPath);

}