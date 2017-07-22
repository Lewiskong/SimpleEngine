#include "FrameAnimation.h"

FrameAnimation::FrameAnimation(Sprite2& sprite)
{
	m_CurrentFrame = 0;
	m_CurrentGroup = 0;
	m_GroupFrameCount = sprite.mFrameSize;
	m_FrameCount = sprite.mFrameSize * sprite.mGroupSize;

	for (int i = 0; i< m_FrameCount ; i++) {
		int gpos = i / m_GroupFrameCount;
		int cpos = i%  m_GroupFrameCount;

		m_Textures[i] = Texture(
				sprite.mWidth,
				sprite.mHeight,
				true, 
				(uint8*)&sprite.mFrames[gpos][cpos].src[0] 
				);
	}
}

void FrameAnimation::OnUpdate(double dt)
{
	m_DeltaTime += dt;
	if( m_DeltaTime  >= 2.0f/60.0f)
	{
		m_DeltaTime = 0;
		m_CurrentFrame++;
		if( m_CurrentFrame >= m_CurrentGroup * (m_GroupFrameCount+1) )
		{
			m_CurrentFrame = m_CurrentGroup * m_GroupFrameCount;
		}
	}
}
