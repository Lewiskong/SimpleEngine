#pragma once

#include "defines.h"


class Texture
{
public:
	Texture(std::string filePath);
	~Texture();
	
	int32 GetWidth() const {return mHeight;}
	int32 GetHeight() const {return mWidth;}
	GLuint GetTextureID() const {return mTextureId;}

private:
	GLuint mTextureId;
	GLint mFormat;
	int32 mWidth,mHeight;
	std::string mPath;

};