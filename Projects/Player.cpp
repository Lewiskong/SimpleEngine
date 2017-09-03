#include "Player.h"
#include "ResourceManager.h"
#include "Demo.h"

//
//map 1501.map
//shape.wdf 49386FCE 54F3FC94
//shape.wd3 DF749306 1BEC0D8A

// PlayerId : 1-12 剑侠客是1
// WeaponId : 0-160 对应某个武器
std::map<uint32, std::vector< uint32>> Player::s_PlayerAnimationTable =
{
	{ 1, { 0x49386FCE, 0x54F3FC94 } }
};

std::map<uint32, std::map<uint32, std::vector< uint32>>> Player::s_WeaponAnimationTable =
{
	{ 1, { { 120, { 0xDF749306, 0x1BEC0D8A } } } }
};


Player::Player(int PlayerId,int WeaponId):
m_PlayerAnimation(2),
m_WeapAnimation(2),
m_AnimationState(Idle)
{
	m_PlayerAnimation[Idle] = new FrameAnimation(
		ResourceManager::GetInstance()->LoadWdfSprite(s_PlayerAnimationTable[PlayerId][Idle])
		);

	m_PlayerAnimation[Moving] = new FrameAnimation(
		ResourceManager::GetInstance()->LoadWdfSprite(s_PlayerAnimationTable[PlayerId][Moving])
		) ;

	m_WeapAnimation[Idle] = new FrameAnimation(
		ResourceManager::GetInstance()->LoadWd3Sprite(s_WeaponAnimationTable[PlayerId][WeaponId][Idle])
		);

	m_WeapAnimation[Moving] = new FrameAnimation(
		ResourceManager::GetInstance()->LoadWd3Sprite(s_WeaponAnimationTable[PlayerId][WeaponId][Moving])
		);
}

Player::~Player()
{

}

void Player::OnUpdate(double dt)
{
	m_PlayerAnimation[m_AnimationState]->OnUpdate(dt);
	m_WeapAnimation[m_AnimationState]->OnUpdate(dt);
}

void Player::OnDraw(SpriteRenderer * renderer, int px,int py)
{
	px = px - m_PlayerAnimation[m_AnimationState]->GetWidth() / 2 + 10;
	py = py - m_PlayerAnimation[m_AnimationState]->GetHeight() + 20;

	m_PlayerAnimation[m_AnimationState]->Draw(renderer, px, py);

	int px2 = px - (m_WeapAnimation[m_AnimationState]->GetKeyX() - m_PlayerAnimation[m_AnimationState]->GetKeyX());
	int py2 = py - (m_WeapAnimation[m_AnimationState]->GetKeyY() - m_PlayerAnimation[m_AnimationState]->GetKeyY());

	m_WeapAnimation[m_AnimationState]->Draw(renderer, px2, py2);
	
}


void Player::SetPos(double x, double y)
{
	m_Pos.x = x;
	m_Pos.y = y;
}

void Player::ResetDirAll(int dir)
{
	m_WeapAnimation[Idle]->Reset(dir);
	m_WeapAnimation[Moving]->Reset(dir);
	m_PlayerAnimation[Idle]->Reset(dir);
	m_PlayerAnimation[Moving]->Reset(dir);
}

void Player::ResetDir(int dir)
{
	m_PlayerAnimation[m_AnimationState]->Reset(dir);
	m_WeapAnimation[m_AnimationState]->Reset(dir);
}

void Player::SetDir(int dir)
{
	m_PlayerAnimation[m_AnimationState]->SetCurrentGroup(dir);
	m_WeapAnimation[m_AnimationState]->SetCurrentGroup(dir);
}


