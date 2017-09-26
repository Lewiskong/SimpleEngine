#include "Player.h"
#include "ResourceManager.h"
#include "Demo.h"
#include "Logger.h"

//
//map 1501.map
//shape.wdf 49386FCE 54F3FC94
//shape.wd3 DF749306 1BEC0D8A

// PlayerId : 1-12 ��������1
// WeaponId : 0-160 ��Ӧĳ������
std::map<uint32, std::vector< uint32>> Player::s_PlayerAnimationTable =
{
	{ 1, { 0x49386FCE, 0x54F3FC94 } }
};

std::map<uint32, std::map<uint32, std::vector< uint32>>> Player::s_WeaponAnimationTable =
{
	{ 1, { { 120, { 0xDF749306, 0x1BEC0D8A } } } }
};


Player::Player(int id ,int PlayerId,int WeaponId):
m_Id(id),
m_PlayerAnimation(2),
m_WeapAnimation(2),
m_AnimationState(Idle),
m_IsMove(false),
m_MoveVelocity(500),
m_UpdateDelta(0),
m_MoveList()
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
	m_UpdateDelta += dt;
	if (m_UpdateDelta >= dt) {
		m_UpdateDelta = 0;
		if (m_IsMove) {
			if (!m_MoveList.empty())
			{
				double localVelocity = m_MoveVelocity*dt;
				Pos d = m_MoveList.front();
				Pos dest;
				dest.x = d.x * 20 + 10;
				dest.y = d.y * 20 + 10;

				if (GMath::Astar_GetDistance(m_Pos.x, m_Pos.y, dest.x, dest.y) > localVelocity) {
					double degree = GMath::Astar_GetAngle(m_Pos.x, m_Pos.y, dest.x, dest.y);

					m_Dir = GMath::Astar_GetDir(degree);

					//Logger::Print("degree:%lf dir:%d \n", degree, m_Dir);

					double stepRangeX = cos(DegreeToRadian(degree));
					double stepRangeY = sin(DegreeToRadian(degree));

					TranslateX(stepRangeX * localVelocity);
					TranslateY(stepRangeY * localVelocity);

					SetDir(m_Dir);
				}
				else {
					Pos d = m_MoveList.front();
					SetX(d.x * 20 + 10);
					SetY(d.y * 20 + 10);
					m_MoveList.pop_front();
				}
			}
			else
			{
				m_IsMove = false;
				SetAnimationState(Player::Idle);
				SetDir(m_Dir);
			}
			//Logger::Print("cur_x:%lf cur_y:%lf\n",GetX(), GetY());
		}

	}

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

void Player::MoveTo(GameMap* gameMapPtr, int destBoxX, int destBoxY)
{
	if (GetBoxX() == destBoxX && GetBoxY() == destBoxY)
	{
		m_MoveList.clear();
		m_IsMove = false;
		SetAnimationState(Player::Idle);
	}
	else
	{
		m_MoveList.clear();
		m_MoveList = gameMapPtr->Move(GetBoxX(), GetBoxY(), destBoxX, destBoxY);
		m_IsMove = true;
		SetAnimationState(Player::Moving);
	}
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


