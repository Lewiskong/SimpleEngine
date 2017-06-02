#include "SpriteBatch.h"
#include "Environment.h"

SpriteBatch::SpriteBatch()
:Singleton<SpriteBatch>()
,m_SpriteQueue()
,m_pShader(nullptr)
{

}

SpriteBatch::~SpriteBatch(void)
{
	delete m_pShader;
}

void SpriteBatch::Init()
{
	std::string vPath =  Environment::GetAbsPath("Shader/MvpVertexShader");
	std::string fPath =  Environment::GetAbsPath("Shader/MvpFragmentShader");

	m_pShader = new Shader(vPath,fPath);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void SpriteBatch::Flush()
{
	Begin();
	End();
}

void SpriteBatch::AddSprite(const SpriteInfo* spriteInfo)
{
	m_SpriteQueue.push_back(spriteInfo);
}

void SpriteBatch::Begin()
{
	/*
	初始化顶点数据等
	*/
	mVertices.clear();
	for(int i=0;i<m_SpriteQueue.size();i++)
	{
		if(i>=BATCHSIZE)break;
		const SpriteInfo* info = m_SpriteQueue[i];

		int x,y,width,height;
		float alpha = info->Alpha;
		x = info->Pos.x;
		y = info->Pos.y;
		width = info->Size.x;
		height = info->Size.y;

		//TL
		mVertices.push_back(x);			//x
		mVertices.push_back(y);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(0);			//tx
		mVertices.push_back(0);			//ty
		mVertices.push_back(alpha);			//alpha

		//TR
		mVertices.push_back(x+width);			//x
		mVertices.push_back(y);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(1);			//tx
		mVertices.push_back(0);			//ty
		mVertices.push_back(alpha);			//alpha


		//BL
		mVertices.push_back(x);			//x
		mVertices.push_back(y+height);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(0);			//tx
		mVertices.push_back(1);			//ty
		mVertices.push_back(alpha);			//alpha

		//BL
		mVertices.push_back(x);			//x
		mVertices.push_back(y+height);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(0);			//tx
		mVertices.push_back(1);			//ty
		mVertices.push_back(alpha);			//alpha

		//TR
		mVertices.push_back(x+width);			//x
		mVertices.push_back(y);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(1);			//tx
		mVertices.push_back(0);			//ty
		mVertices.push_back(alpha);			//alpha

		//BR
		mVertices.push_back(x+width);			//x
		mVertices.push_back(y+height);			//y
		mVertices.push_back(0);			//z
		mVertices.push_back(1);			//tx
		mVertices.push_back(1);			//ty
		mVertices.push_back(alpha);			//alpha
	}
	GLfloat vertices[mVertices.size()];
	for(int i=0;i<mVertices.size();i++)
	{
		vertices[i] = mVertices[i];
	}

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof( vertices),vertices, GL_STATIC_DRAW);

    // Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
    // TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void SpriteBatch::End()
{
	glm::mat4 view;
	glm::mat4 projection;   
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
	projection = glm::ortho(0.0f, 800.0f,600.0f,0.0f, -100.0f, 100.0f);
   // Get the uniform locations
	modelLoc = glGetUniformLocation(m_pShader->GetProgramID(), "model");
	viewLoc = glGetUniformLocation(m_pShader->GetProgramID(), "view");
	projLoc = glGetUniformLocation(m_pShader->GetProgramID(), "projection");
	

	view=glm::mat4();

	m_pShader->Bind();

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*) (&view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)(&projection));

	glBindVertexArray(VAO);
	int triangles = 0;
	for(const SpriteInfo* info : m_SpriteQueue)
	{
		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, info->TextureID);
		glUniform1i(glGetUniformLocation(m_pShader->GetProgramID(), "textureSampler"), 0);
		 // Calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model;

		glm::vec3 s(0.3,0.3,0);
		 model = glm::scale(model,s);
		 model = glm::translate(model,glm::vec3(-30.0f,-30.0f,0.0f));        

        // auto pp =  projection * model * view * glm::vec4(pos,1.0f);
        //std::cout << " pos x:" << pp.x * 800 << " pos y:" << pp.y * -600<< " z:"  << pp.z << " w:" << pp.w << std::endl;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE,  (GLfloat*)(&model));

		glDrawArrays(GL_TRIANGLES, triangles , triangles+6);
		triangles+=6;     
	}
	glBindVertexArray(0);
	
}





