#include "Engine.h"	
#include "SpriteBatch.h"

//non-const static data member must be initialized out of line
Engine * Engine::p_Engine = nullptr;

Engine::~Engine()
{

}

Engine* Engine::GetInstance()
{
	if(p_Engine == nullptr)
	{	
		p_Engine = new Engine();
	}
	return p_Engine;
}

Engine::Engine()
{

}

GLfloat vertices3D[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 cubePositions[] = {
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
Shader* p_Shader;
Shader* p_Shader3D;

 // Set up our vertex data (and buffer(s)) and attribute pointers
std::vector<GLfloat>  vertices1;

std::vector<GLfloat>  colors;

GLuint VBO, VAO, EBO;

GLuint VBO2, VAO2;

Texture * p_Texture;

void Engine::Init()
{
    //SpriteBatch::GetInstance()->Init();
    std::string vPath =  Environment::GetAbsPath("Shader/MvpVertexShader");
    std::string fPath =  Environment::GetAbsPath("Shader/MvpFragmentShader");
    p_Shader = new Shader(vPath,fPath);
    
    p_Texture = new Texture("/Users/oceancx/SimpleEngine/Resource/Assets/bizhi.jpg");
    int tw = p_Texture->GetWidth();
    int th = p_Texture->GetHeight();
    std::cout<<" tw::" << tw<<std::endl;
    std::vector<glm::vec4> textureVertices;
    textureVertices.push_back(glm::vec4(0,0,0,0));
    textureVertices.push_back(glm::vec4(tw,0,1,0));
    textureVertices.push_back(glm::vec4(tw,th,1,1));

    textureVertices.push_back(glm::vec4(0,0, 0,0));
    textureVertices.push_back(glm::vec4(0,th,0,1));
    textureVertices.push_back(glm::vec4(tw,th,1,1));
    vertices1.clear();
    for(int i=0;i<6;i++)
    {
        auto tv = textureVertices[i];
        vertices1.push_back(tv.x);
        vertices1.push_back(tv.y);
        vertices1.push_back(0.0f);
        vertices1.push_back(tv.z);
        vertices1.push_back(tv.w);
    }
    GLfloat vertices[30];//=new GLfloat[6*5];
    for(int i=0;i<vertices1.size();i++)
    {
        vertices[i]=vertices1[i];
    }


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof( vertices),vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Setup some OpenGL options
    glEnable(GL_DEPTH_TEST);
    

    vPath =  Environment::GetAbsPath("Shader/Mvp3DVertexShader");
    fPath =  Environment::GetAbsPath("Shader/Mvp3DFragmentShader");
    p_Shader3D = new Shader(vPath,fPath);


    glGenVertexArrays(1, &VAO2);
    glGenBuffers(1, &VBO2);
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof( vertices3D),vertices3D, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void Engine::Update()
{

}

void Engine::Draw()
{
	p_Shader->Bind();

	// Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, p_Texture->GetTextureID());
    glUniform1i(glGetUniformLocation(p_Shader->GetProgramID(), "textureSampler"), 0);
 

    glm::mat4 view;
    
    glm::mat4 projection;   
    projection = glm::ortho(0.0f, 800.0f,600.0f,0.0f, -1.0f, 1.0f);

    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(p_Shader->GetProgramID(), "model");
    GLint viewLoc = glGetUniformLocation(p_Shader->GetProgramID(), "view");
    GLint projLoc = glGetUniformLocation(p_Shader->GetProgramID(), "projection");

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*) (&view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)(&projection));

    glBindVertexArray(VAO);
    for(GLuint i = 0; i < 10; i++)
    {
        // Calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model;

        glm::vec3 s(0.3,0.3,0);
        model = glm::scale(model,s);
        model = glm::translate(model,glm::vec3(50.0f,40.0f,0.0f));        
        
        // auto pp =  projection * model * view * glm::vec4(pos,1.0f);
        //std::cout << " pos x:" << pp.x * 800 << " pos y:" << pp.y * -600<< " z:"  << pp.z << " w:" << pp.w << std::endl;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,  (GLfloat*)(&model));

        glDrawArrays(GL_TRIANGLES, 0, 36);          
    }
    glBindVertexArray(0);
    
    p_Shader3D->Bind();

    // Bind Textures using texture units
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, p_Texture->GetTextureID());
    glUniform1i(glGetUniformLocation(p_Shader3D->GetProgramID(), "textureSampler"), 0);
    
    // Create camera transformation
    glm::vec3 pos = glm::vec3(0.5f,0.0f,0.0f);
    glm::vec3 front= glm::vec3(0.4f,0.3f,-1.0f);
    glm::vec3 up= glm::vec3(0.0f,1.0f,0.0f);
    view = glm::lookAt(pos, pos+front, up);
    
    projection = glm::perspective(45.0f, 800.0f/600.0f, 0.1f, 1000.0f);
    
    // Get the uniform locations
    modelLoc = glGetUniformLocation(p_Shader3D->GetProgramID(), "model");
    viewLoc = glGetUniformLocation(p_Shader3D->GetProgramID(), "view");
    projLoc = glGetUniformLocation(p_Shader3D->GetProgramID(), "projection");

    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (GLfloat*) (&view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (GLfloat*)(&projection));

    glBindVertexArray(VAO2);
    for(GLuint i = 0; i < 10; i++)
    {
        // Calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model;
         model = glm::translate(model,cubePositions[i]);        
        
        // GLfloat angle = 20.0f * i; 
        // model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));

        auto pp =  projection * model * view * glm::vec4(pos,1.0f);
        std::cout << " pos x:" << pp.x * 800 << " pos y:" << pp.y * -600<< " z:"  << pp.z << " w:" << pp.w << std::endl;
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE,  (GLfloat*)(&model));

        glDrawArrays(GL_TRIANGLES, 0, 36);          
    }
    glBindVertexArray(0);

}