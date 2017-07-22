#pragma once 

#include "ThirdParty/NetEase/Sprite2.h"
#include "Texture.h"
#include <vector>

class FrameAnimation
{
public:
	FrameAnimation(Sprite2& sprite);
	~FrameAnimation();

	int GetCurrentFrame() { return m_CurrentFrame;}
	int GetFrameCount() { return m_FrameCount;}
	int GetCurrentGroup() { return m_CurrentGroup;}
	int GetGroupFrameCount() { return m_GroupFrameCount;}

	const Texture& GetFrame() { return m_Textures[m_CurrentFrame];}

	void OnUpdate(double dt);

	int m_FrameCount;
	int m_CurrentFrame;
	int m_CurrentGroup;
	int m_GroupFrameCount;

	double m_DeltaTime;
 	

	std::vector<Texture> m_Textures;
};