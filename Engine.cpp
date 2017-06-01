#include "Engine.h"	

Engine * Engine::p_Engine = nullptr;


Engine::~Engine()
{

}

Engine* Engine::GetInstance()
{
	if(p_Engine == nullptr )
	{	
		p_Engine = new Engine();
	}
	return p_Engine;
}

Engine::Engine()
{

}

Shader* p_Shader ;

GLfloat vertices[] = {
    // Positions         // Colors         // Texture Coords
     0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // Top Left
};
	// GLfloat vertices[] = {
 //         0.5f,  0.5f, 0.0f,  // Top Right
 //         0.5f, -0.5f, 0.0f,  // Bottom Right
 //        -0.5f, -0.5f, 0.0f,  // Bottom Left
 //        -0.5f,  0.5f, 0.0f   // Top Left 
 //    };
   GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    GLuint VBO, VAO, EBO;
    Texture * p_Texture;
void Engine::Init()
{
	p_Shader = new Shader(Environment::GetAbsPath("Shader/TextureVertexShader"),
		Environment::GetAbsPath("Shader/TextureFragmentShader"));
    
    p_Texture = new  Texture("/Users/oceancx/SimpleEngine/Resource/Assets/wall.jpg");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // TexCoord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); // Unbind VAO

    glBindBuffer(GL_ARRAY_BUFFER, 0);
   

    
}

void Engine::Update()
{

}

void Engine::Draw()
{
	p_Shader->Bind();
    
	glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D,p_Texture->GetTextureID());
        //glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    

	glBindVertexArray(0);
	
}