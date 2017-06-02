# CMake entry point
cmake_minimum_required (VERSION 3.1)
project (SimpleEngine)

set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
set(DIR_COMMONLIB "/Users/oceancx/CommonLib")

add_definitions(
	-std=c++11
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

link_directories(
	${DIR_COMMONLIB}/lib/
)

include_directories(
	${DIR_COMMONLIB}/include/
	.
)

find_library(OpenGL_LIBRARY OpenGL)
find_library(Cocoa_LIBRARY Cocoa)
find_library(IOKit_LIBRARY IOKit)
find_library(CoreVideo_LIBRARY CoreVideo)

set(ALL_LIBS
	${Cocoa_LIBRARY} 
	${OpenGL_LIBRARY} 
	${IOKit_LIBRARY} 
	${CoreVideo_LIBRARY}
	glfw3
	GLEW_1130
	SOIL
	assimp
	freetype
)

add_executable(${PROJECT_NAME}
program.cpp
Environment.h
#main.cpp
global.h
defines.h
Window.h
Window.cpp
TextureManager.h
TextureManager.cpp
Texture.h
Texture.cpp
Sprite.h
Sprite.cpp
SpriteBatch.h
SpriteBatch.cpp
Singleton.h
Singleton.inl
Shader.h
Shader.cpp
SenceManager.h
SenceManager.cpp
Game.h
Game.cpp
Engine.h
Engine.cpp
Shader/SimpleVertexShader.vert
Shader/SimpleFragmentShader.frag
Shader/MvpFragmentShader
Shader/MvpVertexShader
)

target_link_libraries(${PROJECT_NAME}
	${ALL_LIBS}
)


set_target_properties(${PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

