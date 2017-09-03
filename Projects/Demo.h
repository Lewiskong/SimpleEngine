#pragma once
#include "defines.h"
#include "IUpdateDraw.h"
#include "../Event/Event.h"
#include "../Engine.h"
#include "Texture.h"
#include "InputManager.h"
#include "../SpriteRenderer.h"
#include "../ThirdParty/NetEase/Sprite2.h"
#include "../ThirdParty/NetEase/WDF.h"
#include "../ThirdParty/NetEase/WAS.h"
#include "GameMap.h"
#include "../Environment.h"
#include "../ResourceManager.h"
#include "Config.h"
#include "../GMath.h"

#include "FrameAnimation.h"
#include "Player.h"



class Demo : public IUpdateDraw, public IMouseEvent
{
public:

	static const int STATE_MOVE;
	static const int STATE_STAND;
	static const int ANIM_CHARACTER;
	static const int ANIM_WEAPON;
	static const int CHARACTOR_BLOCK_OFFSET_X;
	static const int CHARACTOR_BLOCK_OFFSET_Y;

	Demo();
	~Demo();
	void Update() override;
	void Draw() override;
	void OnEvent(int button, int action, int mods) override;

	void ProcessInput();
	void SetState(int state);
	
	
	// Game-related State data
	SpriteRenderer  *Renderer;
	
	GLfloat delta = 0;

	int dir = 0;
	
	int m_State = STATE_STAND;

	double src_x = 0 , src_y = 0 ;
	double cur_x, cur_y;
	double dest_x = src_x, dest_y= src_y;


	double step_range_x = 0;
	double step_range_y = 0;
	double move_velocity = 500;
	Pos dest;

	float ScreenWidth = 800.0f;
	float ScreenHeight = 600.0f;
	Texture* m_pBlockTexture;


	int actor_state = 1;

	std::list<Pos> mMoveList;
	bool bmove = true;

	int cur_frame = 0;
	int frame_count = 0;
	GameMap* mGameMap;



	int cnt = 0;
	GLfloat delta2=0;
	bool draw_cell = false;


	FrameAnimation* m_Anims[2][2];
	Player * m_Strider;

};


