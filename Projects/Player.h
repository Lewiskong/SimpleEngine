#pragma once

#include "defines.h"
#include "FrameAnimation.h"
#include "Pos.h"
#include "Config.h"



class Player 
{
public:
	enum AnimationState : int 
	{
		Idle = 0,
		Moving= 1
	};

	static std::map<uint32, std::vector< uint32 >> s_PlayerAnimationTable;
	static std::map<uint32, std::map<uint32, std::vector<uint32>> > s_WeaponAnimationTable;
	
	
	Player(int PlayerAnimationId,int WeapAnimationId);
	~Player();
	void OnUpdate(GLfloat dt);
	void OnDraw();
	void ResetDir(int dir);

	const std::vector<FrameAnimation*>& GetWeaponAnimation() const;
	const std::vector<FrameAnimation*>& GetPlayerAnimation() const;
	 

private:
	std::vector<FrameAnimation*> m_WeapAnimation;
	std::vector<FrameAnimation*> m_PlayerAnimation;
	int m_AnimationState;
	int m_Dir;
	Pos m_Pos;

	std::vector<int> m_Test;
	
};