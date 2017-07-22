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

class Demo : public IUpdateDraw, public IMouseEvent
{
public:
	Demo();
	~Demo();
	void Update() override;
	void Draw() override;
	void OnEvent(int button, int action, int mods) override;

	void ProcessInput();
	void toggleActorState();
	
	// Game-related State data
	SpriteRenderer  *Renderer;
	std::vector<std::vector<Texture*>> mSpriteTextures;

	std::vector<Sprite2> mSprite2;


	int dir_count = 0;
	GLfloat delta = 0;

	int dir = 0;
	//右下，左下，左上，右上，下，左，上，右
	int dirs[8] = { 0,1,2,3,4,5,6,7 };

	//↑ → ↓ ← ↗ ↘ ↙ ↖
	double src_x , src_y ;
	double cur_x, cur_y;
	double dest_x = src_x, dest_y= src_y;


	double step_range_x = 0;
	double step_range_y = 0;
	double move_velocity = 500;
	Pos dest;

	float ScreenWidth = 800.0f;
	float ScreenHeight = 600.0f;
	Texture* p_Texture2;


	int actor_state = 1;

	std::list<Pos> mMoveList;
	bool bmove = true;

	int cur_frame = 0;
	int frame_count = 0;
	GameMap* mGameMap;



	int cnt = 0;
	GLfloat delta2=0;
	bool draw_cell = false;

};