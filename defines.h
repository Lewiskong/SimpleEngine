#pragma once
#include <stdint.h>

typedef int64_t 	int64;
typedef int32_t 	int32;
typedef int16_t 	int16;
typedef int8_t 		int8;

typedef uint64_t	uint64;
typedef uint32_t 	uint32;
typedef uint16_t 	uint16;
typedef uint8_t 	uint8;

typedef float		float32;
typedef double		float64;
typedef long double float128;


typedef uint8_t BYTE,  byte;
typedef uint8_t PBYTE;

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>


template <typename T>
inline void SafeDelete(T * &pointer)
{
	if(pointer != nullptr)
	{
		delete pointer;
		pointer = nullptr;
	}
}