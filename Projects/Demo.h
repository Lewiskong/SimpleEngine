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

	
	Demo();
	~Demo();

	static float s_ScreenWidth; 
	static float s_ScreenHeight;

	static int GetScreenWidth(){ return s_ScreenWidth; };
	static int GetScreenHeight(){ return s_ScreenHeight; };

	void Update() override;
	void Draw() override;
	void OnEvent(int button, int action, int mods) override;

	void ProcessInput();
	
	// Game-related State data
	SpriteRenderer  *Renderer;
	
	GLfloat delta = 0;

	int dir = 0;
	

	double src_x = 0 , src_y = 0 ;
	
	double dest_x = src_x, dest_y= src_y;


	double step_range_x = 0;
	double step_range_y = 0;
	double move_velocity = 500;
	Pos dest;

	
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

	Player * m_Strider;

};


