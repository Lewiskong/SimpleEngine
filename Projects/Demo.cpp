#include "Demo.h"

#include "FrameAnimation.h"
#include "Logger.h"


float Demo::s_ScreenWidth = 800.0f;
float Demo::s_ScreenHeight = 600.0f;
bool g_IsTest = true;
void Demo::OnEvent(int button, int action, int mods) 
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int halfScreenWidth = GetScreenWidth() / 2;
		int halfScreenHeight = GetScreenHeight() / 2;

		int mapOffsetX = halfScreenWidth - m_StriderPtr->GetX();
		int mapOffsetY = halfScreenHeight - m_StriderPtr->GetY();
		
		mapOffsetX = GMath::Clamp(mapOffsetX, -m_GameMapPtr->GetWidth() + s_ScreenWidth, 0);
		mapOffsetY = GMath::Clamp(mapOffsetY, -m_GameMapPtr->GetHeight() + s_ScreenHeight, 0);

		double mouseX = InputManager::GetInstance()->GetMouseX();
		double mouseY = InputManager::GetInstance()->GetMouseY();
		
		m_StriderPtr->MoveTo(m_GameMapPtr,(-mapOffsetX + mouseX) / 20,(-mapOffsetY + mouseY) / 20);
	}
}

Demo::Demo()
{
	InputManager::GetInstance()->SetMouseEvent(this);
	
	m_RendererPtr = new SpriteRenderer();

	m_GameMapPtr = new GameMap(0);

	auto blockPath = Environment::GetAbsPath("Resource/Assets/wall.jpg");
	m_BlockTexturePtr = new Texture(blockPath);

	m_StriderPtr = new Player(1, 120);
	
	m_StriderPtr->SetPos(300, 300);

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
	
	m_StriderPtr->OnUpdate(dt);
	
	for (Player* npc : m_NPCs)
	{
		npc->OnUpdate(dt);
	}
	
	ProcessInput();

	if (m_IsChangeState) 
	{
		m_ChangeStateTimeInterval += dt;
		if (m_ChangeStateTimeInterval >= 20 * dt )
		{
			m_IsChangeState = false;
			m_ChangeStateTimeInterval = 0;
		}
	}
}

void Demo::ProcessInput()
{
	int amout = 1;
	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_W))
	{
		m_StriderPtr->TranslateY(-amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_StriderPtr->GetX(), m_StriderPtr->GetY());
		if (g_IsTest)
		{
			g_IsTest = false;
			m_NPCs[0]->MoveTo(m_GameMapPtr, (2450-10) / 20 , (370-10) / 20);
		}
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_A))
	{
		m_StriderPtr->TranslateX(-amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_StriderPtr->GetX(), m_StriderPtr->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_S))
	{
		m_StriderPtr->TranslateY(amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_StriderPtr->GetX(), m_StriderPtr->GetY());
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_D))
	{
		m_StriderPtr->TranslateX(amout);
		Logger::Print("cur_x:%lf cur_y:%lf\n", m_StriderPtr->GetX(), m_StriderPtr->GetY());
	}

	int dir = 0;

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_3) || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_3))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_E);
		m_StriderPtr->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_1)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_1))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S_W);
		m_StriderPtr->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_7)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_7))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N_W);
		m_StriderPtr->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_9)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_9))
	{
		dir = static_cast<int>(FrameAnimation::Dir::N_E);
		m_StriderPtr->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_2)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_2))
	{
		dir = static_cast<int>(FrameAnimation::Dir::S);
		m_StriderPtr->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_4)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_4))
	{
		dir = static_cast<int>(FrameAnimation::Dir::W);
		m_StriderPtr->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_8)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_8))
	{

		dir = static_cast<int>(FrameAnimation::Dir::N);
		m_StriderPtr->SetDir(dir);
	}


	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_6)  || InputManager::GetInstance()->IsKeyUp(GLFW_KEY_6))
	{
		dir = static_cast<int>(FrameAnimation::Dir::E);
		m_StriderPtr->SetDir(dir);
	}

	if (InputManager::GetInstance()->IsKeyUp(GLFW_KEY_KP_5) && !m_IsChangeState)
	{
		m_IsChangeState = true;
		
		if ( m_StriderPtr->GetAnimationState() == Player::Moving)
		{
			m_StriderPtr->SetAnimationState(Player::Idle);
		}
		else
		{
			m_StriderPtr->SetAnimationState(Player::Moving);
		}
		m_StriderPtr->ResetDir(dir);
	}

}

void Demo::Draw()
{
	
	m_GameMapPtr->Draw(m_RendererPtr, m_StriderPtr->GetX(), m_StriderPtr->GetY());
	
	int screenWidth = Demo::GetScreenWidth();
	int screenHeight = Demo::GetScreenHeight();
	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;
	int mapOffsetX = halfScreenWidth - m_StriderPtr->GetX();
	int mapOffsetY = halfScreenHeight - m_StriderPtr->GetY();
	int mapWidth = m_GameMapPtr->GetWidth();
	int mapHeight = m_GameMapPtr->GetHeight();
	
	int px = m_StriderPtr->GetX();
	int py = m_StriderPtr->GetY();

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

	m_StriderPtr->OnDraw(m_RendererPtr,px,py);


	for (Player* npc : m_NPCs)
	{
		npc->OnDraw(m_RendererPtr, npc->GetX() + mapOffsetX, npc->GetY() + mapOffsetY);
	}

	m_GameMapPtr->DrawMask(m_RendererPtr, m_StriderPtr->GetX(), m_StriderPtr->GetY());
	
	//m_GameMapPtr->DrawCell(m_RendererPtr, mapOffsetX, mapOffsetY);
}

