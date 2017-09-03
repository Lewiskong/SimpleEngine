#include "Player.h"
#include "ResourceManager.h"

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
m_WeapAnimation(2)
{
	m_PlayerAnimation[Idle] =   new FrameAnimation(
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

void Player::OnUpdate(GLfloat dt)
{

}

void Player::OnDraw()
{

}

void Player::ResetDir(int dir )
{
	//for (int i = 0; i < 2; i++)
	//	for (int j = 0; j < 2; j++)
	//	{
	//		//m_Strider->Reset(dir);
	//		m_Anims[i][j]->Reset(dir);
	//	}

	m_WeapAnimation[Idle]->Reset(dir);
	m_WeapAnimation[Moving]->Reset(dir);
	m_PlayerAnimation[Idle]->Reset(dir);
	m_PlayerAnimation[Moving]->Reset(dir);

}

const std::vector<FrameAnimation*>& Player::GetWeaponAnimation() const
{
	return m_WeapAnimation;
}

const std::vector<FrameAnimation*>& Player::GetPlayerAnimation() const
{
	return m_PlayerAnimation;
}
