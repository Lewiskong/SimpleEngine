#include "Demo.h"

#include "FrameAnimation.h"
#include "Logger.h"

bool changeState = false;
double ddt = 0;
float Demo::s_ScreenWidth = 800.0f;
float Demo::s_ScreenHeight = 600.0f;

void Demo::OnEvent(int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << " OnEvent : call success!" << std::endl;
		mMoveList.clear();

		int halfScreenWidth = GetScreenWidth() / 2;
		int halfScreenHeight = GetScreenHeight() / 2;

		int mapOffsetX = halfScreenWidth - m_Strider->GetX();
		int mapOffsetY = halfScreenHeight - m_Strider->GetY();
		
		mapOffsetX = GMath::Clamp(mapOffsetX, -mGameMap->GetWidth() + s_ScreenWidth, 0);
		mapOffsetY = GMath::Clamp(mapOffsetY, -mGameMap->GetHeight() + s_ScreenHeight, 0);

		double mouse_x = InputManager::GetInstance()->GetMouseX();
		double mouse_y = InputManager::GetInstance()->GetMouseY();
		mMoveList = mGameMap->Move(m_Strider->GetBoxX(),m_Strider->GetBoxY(), (-mapOffsetX + mouse_x) / 20,
			(-mapOffsetY + mouse_y) / 20);

		Logger::Print("box X:%lf  Y:%lf \n", (-mapOffsetX + mouse_x) / 20, (-mapOffsetY + mouse_y) / 20);
		bmove = true;
		
		m_Strider->SetAnimationState(Player::Moving);
	}
}

Demo::Demo()
{
	
	InputManager::GetInstance()->SetMouseEvent(this);
	
	m_RendererPtr = new SpriteRenderer();

	mGameMap = new GameMap(0);

	auto blockPath = Environment::GetAbsPath("Resource/Assets/wall.jpg");
	m_pBlockTexture = new Texture(blockPath);

	m_Strider = new Player(1, 120);
	
	m_Strider->SetPos(300, 300);

	mMoveList = mGameMap->Move(m_Strider->GetBoxX(), m_Strider->GetBoxY() , m_Strider->GetBoxX(), m_Strider->GetBoxY());

	dir = (int) FrameAnimation::Dir::S_E;
	m_Strider->ResetDirAll(dir);

	int birthPos[10][2] = 
	{
		{ 400, 300},
		{ 600, 900 },
		{ 1550, 300 },
		{ 600, 1900 },
		{ 400, 2000 },
		{ 2600, 400 },
		{ 3400, 800 },
		{ 4600, 900 },
		{ 2400, 300 },
		{ 600, 900 },
	};

	
	for (int i = 0; i < 10; i++)
	{
		Player* player = new Player(1, 120);
		player->SetPos(birthPos[i][0], birthPos[i][1]);
		player->ResetDirAll(i % 8);
		m_NPCs.push_back(player);
		i++;
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

				if (GMath::Astar_GetDistance(m_Strider->GetX(), m_Strider->GetY(), dest.x, dest.y) > local_velocity) {
					double degree = GMath::Astar_GetAngle(m_Strider->GetX(), m_Strider->GetY(), dest.x, dest.y);

					dir = GMath::Astar_GetDir(degree);

					Logger::Print("degree:%lf dir:%d \n", degree, dir);

					step_range_x = cos(DegreeToRadian(degree));
					step_range_y = sin(DegreeToRadian(degree));

					m_Strider->TranslateX(step_range_x * local_velocity);
					m_Strider->TranslateY(step_range_y * local_velocity);
					
					m_Strider->SetDir(dir);
				}
				else {
					Pos d = mMoveList.front();
					m_Strider->SetX(d.x * 20 + 10);
					m_Strider->SetY(d.y * 20 + 10);
					mMoveList.pop_front();
				}
			}
			else
			{
				bmove = false;
				m_Strider->SetAnimationState(Player::Idle);
				m_Strider->SetDir(dir);
			}
			Logger::Print("cur_x:%lf cur_y:%lf\n", m_Strider->GetX(),m_Strider->GetY());
		}
		
	}

	m_Strider->OnUpdate(dt);

	for (Player* npc : m_NPCs)
	{
		npc->OnUpdate(dt);
	}
	
	
	

	ProcessInput();

	if (changeState)
		ddt += dt;

	if (ddt >= 20 * dt && changeState)
	{
		changeState = false;
		ddt = 0;
	}
}

void Demo::ProcessInput()
{
	int amout = 1;
	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_W))
	{
		m_Strider->TranslateY(-amout);

		Logger::Print("cur_x:%lf cur_y:%lf\n", m_Strider->GetX(), m_Strider->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_A))
	{
		m_Strider->TranslateX(-amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_Strider->GetX(), m_Strider->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_S))
	{
		m_Strider->TranslateY(amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_Strider->GetX(), m_Strider->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_D))
	{
		m_Strider->TranslateX(amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_Strider->GetX(), m_Strider->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_3) || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_3))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_E);
		m_Strider->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_1)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_1))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_W);
		m_Strider->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_7)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_7))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N_W);
		m_Strider->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_9)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_9))
	{
		dir = static_cast<int>(FrameAnimation::Dir::N_E);
		m_Strider->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_2)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_2))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S);
		m_Strider->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_4)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_4))
	{
		dir = static_cast<int>(FrameAnimation::Dir::W);
		m_Strider->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_8)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_8))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N);
		m_Strider->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_6)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_6))
	{
		dir = static_cast<int>(FrameAnimation::Dir::E);
		m_Strider->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_5) && !changeState)
	{
		changeState = true;
		
		if ( m_Strider->GetAnimationState() == Player::Moving)
		{
			m_Strider->SetAnimationState(Player::Idle);
		}
		else
		{
			m_Strider->SetAnimationState(Player::Moving);
		}
		m_Strider->ResetDir(dir);
	}

}

void Demo::Draw()
{
	
	mGameMap->Draw(m_RendererPtr, m_Strider->GetX(), m_Strider->GetY());
	
	int screenWidth = Demo::GetScreenWidth();
	int screenHeight = Demo::GetScreenHeight();
	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;
	int mapOffsetX = halfScreenWidth - m_Strider->GetX();
	int mapOffsetY = halfScreenHeight - m_Strider->GetY();
	int mapWidth = mGameMap->GetWidth();
	int mapHeight = mGameMap->GetHeight();
	
	int px = m_Strider->GetX();
	int py = m_Strider->GetY();

	mapOffsetX = GMath::Clamp(mapOffsetX, -mapWidth + screenWidth, 0);
	mapOffsetY = GMath::Clamp(mapOffsetY, -mapHeight + screenHeight, 0);
	
	int maxMapOffsetX = mapWidth - halfScreenWidth;
	int maxMapOffsetY = mapHeight - halfScreenHeight;
	
	px = px < halfScreenWidth ? px :
		(px  > maxMapOffsetX ?
		(screenWidth - (mapWidth - px)) : halfScreenWidth);
	py = py < halfScreenHeight ? py :
		(py> maxMapOffsetY ?
		(screenHeight - (mapHeight - py)) : halfScreenHeight);

	m_Strider->OnDraw(m_RendererPtr,px,py);


	for (Player* npc : m_NPCs)
	{
		npc->OnDraw(m_RendererPtr, npc->GetX() + mapOffsetX, npc->GetY() + mapOffsetY);
	}



	mGameMap->DrawMask(m_RendererPtr, m_Strider->GetX(), m_Strider->GetY());
	//Logger::Print("%lf %lf\n", cur_x, cur_y);
	//mGameMap->DrawCell(m_RendererPtr, mapOffsetX, mapOffsetY);
}

