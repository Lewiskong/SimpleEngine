#include "Window.h"

#include "global.h"
#include "Shader.h"
#include "Environment.h"
#include "InputManager.h"

Window::Window(int width,int height)
{

    // Init GLFW
	glfwInit();
    // Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
	p_Window = glfwCreateWindow(width, height, WINDOW_TITLE, nullptr, nullptr);
	glfwMakeContextCurrent(p_Window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

    // Define the viewport dimensions
	// int width, height;
	glfwGetFramebufferSize(p_Window, &width, &height);
	glViewport(0, 0, width, height);

    p_Game = new Game(width,height,WINDOW_TITLE);
    InputManager::GetInstance()->Init(p_Window);

}

Window::~Window()
{
	
}


void Window::Show()
{
    glEnable(GL_DEPTH_TEST);

    p_Game->Start();

	 // Game loop
    while (!glfwWindowShouldClose(p_Window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
    	glfwPollEvents();

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        p_Game->Update();
        
        p_Game->Draw();

        // Swap the screen buffers
        glfwSwapBuffers(p_Window);
    }
    
    p_Game->End();
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
}


