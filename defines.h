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
#include <list>
#include <map>

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



#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为4字节对齐
// TGA 文件头
struct TGA_FILE_HEADER
{
	uint8 IdLength;             // 图像信息字段(默认:0)
	uint8 ColorMapType;         // 颜色标的类型(默认0)
	uint8 ImageType;            // 图像类型码(支持2或10)
	uint16 ColorMapFirstIndex;  // 颜色表的引索(默认:0)
	uint16 ColorMapLength;      // 颜色表的长度(默认:0)
	uint8 ColorMapEntrySize;    // 颜色表表项的为数(默认:0，支持16/24/32)
	uint16 XOrigin;             // 图像X坐标的起始位置(默认:0)
	uint16 YOrigin;             // 图像Y坐标的起始位置(默认:0)
	uint16 ImageWidth;          // 图像的宽度
	uint16 ImageHeight;         // 图像的高度
	uint8 PixelDepth;           // 图像每像素存储占用位数
	uint8 ImageDescruptor;      // 图像描述字符字节(默认:0，不支持16bit 565格式)
};
#pragma pack(pop)//恢复对齐状态
