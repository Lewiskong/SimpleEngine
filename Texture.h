#pragma once

#include "defines.h"


class Texture
{
public:
	Texture(std::string filePath);
	~Texture();
	
	int32 GetWidth() const {return mWidth;}
	int32 GetHeight() const {return mHeight;}
	GLuint GetTextureID() const {return mTextureId;}

private:
	GLuint mTextureId;
	GLint mFormat;
	int32 mWidth,mHeight;
	std::string mPath;

};