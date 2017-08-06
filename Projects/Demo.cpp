#include "Demo.h"

#include "FrameAnimation.h"
#include "Logger.h"

const int Demo::STATE_MOVE = 1;
const int Demo::STATE_STAND = 0;
const int Demo::ANIM_CHARACTER = 0;
const int Demo::ANIM_WEAPON = 1;

const int CHARACTOR_BLOCK_OFFSET_X=0;
const int CHARACTOR_BLOCK_OFFSET_Y=10;

bool changeState = false;
double ddt = 0;
void Demo::OnEvent(int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << " OnEvent : call success!" << std::endl;
		mMoveList.clear();

		int mapOffsetX = ScreenWidth / 2 - cur_x;
		int mapOffsetY = ScreenHeight / 2 - cur_y;
		
		mapOffsetX = GMath::Clamp(mapOffsetX,-mGameMap->GetWidth() + ScreenWidth,0);
		mapOffsetY = GMath::Clamp(mapOffsetY,-mGameMap->GetHeight() + ScreenHeight,0);

		double mouse_x = InputManager::GetInstance()->GetMouseX();
		double mouse_y = InputManager::GetInstance()->GetMouseY();
		mMoveList = mGameMap->Move(cur_x / 20, cur_y / 20, (-mapOffsetX + mouse_x) / 20,
			(-mapOffsetY + mouse_y) / 20);

		Logger::Print("box X:%lf  Y:%lf \n", (-mapOffsetX + mouse_x) / 20, (-mapOffsetY + mouse_y) / 20);
		bmove = true;
		//SetState(STATE_MOVE);
		m_State = STATE_MOVE;
		
	}
}

Demo::Demo()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	InputManager::GetInstance()->SetMouseEvent(this);

	std::string vPath =  Environment::GetAbsPath("Shader/sprite.vs");
	std::string fPath =  Environment::GetAbsPath("Shader/sprite.frag");
	std::cout <<" vPath:" << vPath << std::endl;
	std::cout <<" fPath:" << fPath << std::endl;

	ResourceManager::LoadShader(vPath, fPath, "", "sprite");

  // Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, 800.0f,600.0f, 0.0f, -1.0f, 1.0f);
	Shader* shader = ResourceManager::GetShader("sprite");
	shader->Bind();

	glUniform1i(glGetUniformLocation(shader->GetProgramID(), "image"), 0);    
	glUniformMatrix4fv(glGetUniformLocation(shader->GetProgramID(), "projection"), 1, GL_FALSE, (GLfloat*) (&projection));

	Renderer = new SpriteRenderer(shader);

   	/*读取配置*/
	Config config(Environment::GetAbsPath("Projects/config.txt" ));
	config.Print();

	std::string path = config.GetMapPath(config.mDict["map"][0]);
	mGameMap = new GameMap(path);

	
	auto blockPath = Environment::GetAbsPath("Resource/Assets/wall.jpg");
	m_pBlockTexture = new Texture(blockPath);

	for (int i = 0; i < 2; i++)
	{
		int id = 0; std::string s = config.mDict["shape.wdf"][i]; sscanf(s.c_str(), "%x", &id);
		NetEase::WDF wdf(config.GetWdfPath("shape.wdf"));
		Sprite2 sprite2=  wdf.LoadSprite(id);

		if (i == 0)
			m_Anims[STATE_STAND][ANIM_CHARACTER]= new FrameAnimation(sprite2);
		if (i == 1)
			m_Anims[STATE_MOVE][ANIM_CHARACTER] = new FrameAnimation(sprite2);
		
	}

	for (int i = 0; i < 2; i++)
	{
		int id = 0; std::string s = config.mDict["shape.wd3"][i]; sscanf(s.c_str(), "%x", &id);
		NetEase::WDF wdf(config.GetWdfPath("shape.wd3"));
		Sprite2 sprite2 = wdf.LoadSprite(id);
		if (i == 0)
			m_Anims[STATE_STAND][ANIM_WEAPON] = new FrameAnimation(sprite2);
		if (i == 1)
			m_Anims[STATE_MOVE][ANIM_WEAPON] = new FrameAnimation(sprite2);
	}

	cur_x = 5000;
	cur_y = 400;

	mMoveList = mGameMap->Move(cur_x/20, cur_y/20, cur_x/20, cur_y/20);

	dir = (int) FrameAnimation::Dir::S_E;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
		{
			m_Anims[i][j]->Reset(dir );
		}

}

Demo::~Demo()
{

}

void Demo::Update()
{
	double dt = Engine::GetInstance()->GetDeltaTime(); 
	
	delta += dt;
	if (delta >= dt) {
		delta = 0;
		if (bmove){
			if (!mMoveList.empty())
			{
				double local_velocity = move_velocity*dt;
				Pos d = mMoveList.front();
				dest.x = d.x * 20 + 10;
				dest.y = d.y * 20 + 10;

				if (GMath::Astar_GetDistance(cur_x, cur_y, dest.x, dest.y) > local_velocity) {
					double degree = GMath::Astar_GetAngle(cur_x, cur_y, dest.x, dest.y);

					dir = GMath::Astar_GetDir(degree);

					Logger::Print("degree:%lf dir:%d \n", degree, dir);

					step_range_x = cos(DegreeToRadian(degree));
					step_range_y = sin(DegreeToRadian(degree));

					cur_x += step_range_x * local_velocity;
					cur_y += step_range_y * local_velocity;

					m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
					m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
				}
				else {
					Pos d = mMoveList.front();
					cur_x = d.x * 20 + 10;
					cur_y = d.y * 20 + 10;
					mMoveList.pop_front();
				}

			}
			else
			{
				bmove = false;
			//	SetState(STATE_STAND);
				m_State = STATE_STAND;
				m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
				m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
			}
			Logger::Print("cur_x:%lf cur_y:%lf\n", cur_x,cur_y);
		}
		
	}



	m_Anims[m_State][ANIM_CHARACTER]->OnUpdate(dt);
	m_Anims[m_State][ANIM_WEAPON]->OnUpdate(dt);

	ProcessInput();

	if (changeState)
		ddt += dt;

	if (ddt >= 20 * dt && changeState)
	{
		changeState = false;
		ddt = 0;
	}
}


void Demo::SetState(int state)
{
	if (!changeState)
	{
		changeState = true;

		m_State = state;
		m_Anims[m_State][ANIM_CHARACTER]->Reset(dir);
		m_Anims[m_State][ANIM_WEAPON]->Reset(dir);
		
	}
}

void Demo::ProcessInput()
{
	int amout = 1;
	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_W))
	{
		cur_y -= amout;
		Logger::Print("cur_x:%lf cur_y:%lf\n", cur_x,cur_y);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_A))
	{
		cur_x -= amout;
		Logger::Print("cur_x:%lf cur_y:%lf\n", cur_x,cur_y);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_S))
	{
		cur_y += amout;
		Logger::Print("cur_x:%lf cur_y:%lf\n", cur_x,cur_y);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_D))
	{
		cur_x += amout;
		Logger::Print("cur_x:%lf cur_y:%lf\n", cur_x,cur_y);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_3) || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_3))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_E);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_1)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_1))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_W);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_7)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_7))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N_W);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_9)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_9))
	{
		dir = static_cast<int>(FrameAnimation::Dir::N_E);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_2)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_2))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_4)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_4))
	{
		dir = static_cast<int>(FrameAnimation::Dir::W);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_8)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_8))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_6)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_6))
	{
		dir = static_cast<int>(FrameAnimation::Dir::E);
		m_Anims[m_State][ANIM_CHARACTER]->SetCurrentGroup(dir);
		m_Anims[m_State][ANIM_WEAPON]->SetCurrentGroup(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_5) && !changeState)
	{
		changeState = true;
		if (m_State == STATE_MOVE)
		{
			m_State = STATE_STAND;
		}
		else
		{
			m_State = STATE_MOVE;
		}

		m_Anims[m_State][ANIM_CHARACTER]->Reset(dir);
		m_Anims[m_State][ANIM_WEAPON]->Reset(dir);

		int cnt1= m_Anims[m_State][ANIM_CHARACTER]->GetGroupFrameCount();
		int cnt2= m_Anims[m_State][ANIM_WEAPON]->GetGroupFrameCount();
		Logger::Print("%d %d\n", cnt1, cnt2);

	}

}

void Demo::Draw()
{
	int halfScreenWidth = ScreenWidth /2;
	int halfScreenHeight = ScreenHeight/2;

	int mapOffsetX = halfScreenWidth - cur_x;
	int mapOffsetY = halfScreenHeight - cur_y;

	mapOffsetX = GMath::Clamp(mapOffsetX,-mGameMap->GetWidth() + ScreenWidth ,0);
	mapOffsetY = GMath::Clamp(mapOffsetY,-mGameMap->GetHeight() + ScreenHeight,0);

	mGameMap->Draw(Renderer, mapOffsetX , mapOffsetY);
	
	int maxMapOffsetX = mGameMap->GetWidth() - halfScreenWidth ;
	int maxMapOffsetY = mGameMap->GetHeight()  - halfScreenHeight;

	int px = cur_x <  halfScreenWidth ? cur_x : 
	(cur_x > maxMapOffsetX ? 
		(ScreenWidth- ( mGameMap->GetWidth() - cur_x) ) : halfScreenWidth );
	int py = cur_y <  halfScreenHeight ? cur_y : 
	(cur_y > maxMapOffsetY ?
		(ScreenHeight- ( mGameMap->GetHeight() - cur_y)) : halfScreenHeight );
	
	px = px - m_Anims[m_State][ANIM_CHARACTER]->GetWidth()/2 + 10;
	py = py - m_Anims[m_State][ANIM_CHARACTER]->GetHeight() + 20; 

	m_Anims[m_State][ANIM_CHARACTER]->Draw(Renderer,px,py);

	int px2 = px - (m_Anims[m_State][ANIM_WEAPON]->GetKeyX() - m_Anims[m_State][ANIM_CHARACTER]->GetKeyX());
	int py2 = py - (m_Anims[m_State][ANIM_WEAPON]->GetKeyY() - m_Anims[m_State][ANIM_CHARACTER]->GetKeyY());
	m_Anims[m_State][ANIM_WEAPON]->Draw(Renderer, px2, py2);
	
	mGameMap->DrawMask(Renderer, mapOffsetX, mapOffsetY);

//		mGameMap->DrawMask(Renderer, mapOffsetX, mapOffsetY);


	//Logger::Print("%lf %lf\n", cur_x, cur_y);
	

  //mGameMap->DrawCell(Renderer, mapOffsetX, mapOffsetY);
}

