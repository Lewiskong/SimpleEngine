#include "InputManager.h"

bool InputManager::mKeys[1024] = {0};

bool InputManager::mFirstMouse = true;

MousePos InputManager::mMousePos(0,0);

void InputManager::KeyCallbackFunc(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if(action == GLFW_PRESS)
        mKeys[key] = true;
    else if(action == GLFW_RELEASE)
        mKeys[key] = false;	
}

void InputManager::ScrollCallbackFunc(GLFWwindow* window, double xoffset, double yoffset)
{
    
}

void InputManager::MouseCallbackFunc(GLFWwindow* window, double xpos, double ypos)
{
    if(mFirstMouse)
    {
        mMousePos.x = xpos;
        mMousePos.y = ypos;
        mFirstMouse = false;
    }

    GLfloat xoffset = xpos - mMousePos.x;
    GLfloat yoffset = mMousePos.y - ypos;  // Reversed since y-coordinates go from bottom to left
    
    mMousePos.x = xpos;
    mMousePos.y = ypos;
}

InputManager::InputManager()
:Singleton<InputManager>()
{
}

InputManager::~InputManager()
{
	m_pWindow = nullptr;
}

void InputManager::Init(GLFWwindow* window)
{
	m_pWindow = window;
}

void InputManager::SetKeyCallback()
{
    glfwSetKeyCallback(m_pWindow, KeyCallbackFunc);
}

void InputManager::SetScrollCallback()
{
    glfwSetScrollCallback(m_pWindow, ScrollCallbackFunc);   
}

void InputManager::SetMouseCallback()
{
	glfwSetCursorPosCallback(m_pWindow, MouseCallbackFunc);
}






