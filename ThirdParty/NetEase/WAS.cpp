#include "WAS.h"
#include <iostream>
// #include <Sprite2.h>
// using namespace std;
WAS::WAS(string filename, int offset, int size)
{
	mFileName = filename;
	mFileOffset = offset;
	mFileSize = size;
	ifstream infile(filename, ios::binary | ios::in);
	infile.seekg(offset, ios::beg);
	infile.read((char*)&mHeader, sizeof(mHeader));
	if (mHeader.flag != 0x5053)
	{
		cerr << "Sprite File Flag Error!" << endl;
		exit(EXIT_FAILURE);
	}

	uint16 palette16[256];
	memset(palette16, 0, sizeof(palette16));
	infile.read((char*)palette16, sizeof(palette16));

	for (int i = 0; i<256; i++)
	{
		mPalette32[i] = RGB565to888(palette16[i], 0xff);
		cout << "color:" << mPalette32[i] << endl;
	}

	int frames = mHeader.group * mHeader.frame;
	mFrameIndecies = new uint32[frames];
	infile.read((char*)mFrameIndecies, frames * 4);
	infile.close();
}

WAS::WAS(fstream &infile, int offset, int size)
{

	mFileOffset = offset;
	mFileSize = size;
	infile.seekg(offset, ios::beg);
	infile.read((char*)&mHeader, sizeof(mHeader));
	if (mHeader.flag != 0x5053)
	{
		cerr << "Sprite File Flag Error!" << endl;
		exit(EXIT_FAILURE);
	}

	uint16 palette16[256];
	memset(palette16, 0, sizeof(palette16));
	infile.read((char*)palette16, sizeof(palette16));

	for (int i = 0; i<256; i++)
	{
		mPalette32[i] = RGB565to888(palette16[i], 0xff);
		cout << "color:" << mPalette32[i] << endl;
	}

	int frames = mHeader.group * mHeader.frame;
	mFrameIndecies = new uint32[frames];
	infile.read((char*)mFrameIndecies, frames * 4);

}


WAS::~WAS()
{

}


uint8 WAS::MixAlpha(uint8 color, uint8 alpha)
{
	// a*C+(1-a)*C
	// uint8 res8=color*alpha/255;
	// printf("%x\n",alpha );
	// std::cout<<"level:" <<alpha<<std::endl;
	// alpha=127;
	printf("c:%x a:%x\n", color, alpha);
	uint32 res = color*alpha / 0xff;
	res = 0;
	return res>0xff ? 0xff : res;
}

/*
加载精灵，调色板
*/
// Sprite2 WAS::LoadSprite(int dir)
// {

// }

uint32 WAS::RGB565to888(uint16 color, uint8 alpha)
{
	unsigned int r = (color >> 11) & 0x1f;
	unsigned int g = (color >> 5) & 0x3f;
	unsigned int b = (color) & 0x1f;
	uint32 R, G, B, A;
	A = alpha;
	R = (r << 3) | (r >> 2);
	G = (g << 2) | (g >> 4);
	B = (b << 3) | (b >> 2);
	return   A << 24 | (B << 16) | (G << 8) | R;
	// return B<<24|G<<16|R<<8|A;
	// return A<<24|R<<16|G<<8|B;
}





// 16bit 565Type Alpha 混合
uint16 WAS::Alpha565(uint16 Src, uint16 Des, uint8 Alpha)
{
	uint16 Result;
	// 混合后的颜色=( ( A-B ) * Alpha ) >> 5 + B
	// 混合后的颜色 = ( A * Alpha + B * ( 32-Alpha ) ) / 32

	unsigned short R_Src, G_Src, B_Src;
	R_Src = G_Src = B_Src = 0;

	R_Src = Src & 0xF800;
	G_Src = Src & 0x07E0;
	B_Src = Src & 0x001F;

	R_Src = R_Src >> 11;
	G_Src = G_Src >> 5;

	unsigned short R_Des, G_Des, B_Des;
	R_Des = G_Des = B_Des = 0;

	R_Des = Des & 0xF800;
	G_Des = Des & 0x07E0;
	B_Des = Des & 0x001F;

	R_Des = R_Des >> 11;
	G_Des = G_Des >> 5;

	unsigned short R_Res, G_Res, B_Res;
	R_Res = G_Res = B_Res = 0;

	R_Res = ((R_Src - R_Des)*Alpha) >> 5 + R_Des;
	G_Res = ((G_Src - G_Des)*Alpha) >> 5 + G_Des;
	B_Res = ((B_Src - B_Des)*Alpha) >> 5 + B_Des;

	//	R_Res = (R_Src*Alpha + R_Des*(32-Alpha)) >> 5;
	//	G_Res = (G_Src*Alpha + G_Des*(32-Alpha)) >> 5;
	//	B_Res = (B_Src*Alpha + B_Des*(32-Alpha)) >> 5;

	R_Res = R_Res << 11;
	G_Res = G_Res << 5;

	Result = R_Res | G_Res | B_Res;
	return Result;
}



