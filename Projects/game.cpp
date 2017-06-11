/******************************************************************/
#include "Game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "MAP.h"
#include "mhxy.h"
#include "WDF.h"
#include "Sprite2.h"
#include <vector>
#include <cmath>
#include "Config.h"
#include <iostream>
#include <SOIL/SOIL.h>
#include "GameMap.h"
#include <algorithm>
#include <list>

// Game-related State data
SpriteRenderer  *Renderer;
std::vector<vector<Texture2D>> mSprites;

Sprite2 sprite, sprite2;

#define PI 3.1415926
#define DegreeToRadian(d) (d*PI/180)
#define RadianToDegree(r) (r*180/PI)


int cur_frame = 0;
int frame_count;
int dir_count = 0;
GLfloat delta = 0;

int dir = 0;
//右下，左下，左上，右上，下，左，上，右
int dirs[8] = { 0,1,2,3,4,5,6,7 };

//↑ → ↓ ← ↗ ↘ ↙ ↖

double src_x , src_y ;
double cur_x, cur_y;
double dest_x = src_x, dest_y= src_y;
GameMap *mGameMap;
std::list<Pos> mMoveList;
double step_range_x = 0;
double step_range_y = 0;
double move_velocity = 500;
Pos dest;

bool bmove = false;


Game::Game(GLuint width, GLuint height)
  : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
  delete Renderer;
}

void Game::Init()
{ 
  ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "sprite");
  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
  // Set render-specific controls
  Shader shader = ResourceManager::GetShader("sprite");
  Renderer = new SpriteRenderer(shader);

  /*读取配置*/
  Config config("config.txt");
  config.Print();

  std::string path = config.GetMapPath(config.mDict["map"][0]);
  mGameMap = new GameMap(path);

  /*读取人物Sprite*/
  NetEase::WDF wdf(config.GetWdfPath("shape.wdf"));
  int id ;
  std::string s = config.mDict["shape.wdf"][0];
  sscanf(s.c_str(),"%x",&id);
  sprite = wdf.LoadSprite(id);
  std::vector<Texture2D> tSprit;
  dir_count = sprite.mGroupSize;
  for (int i = 0; i<sprite.mFrameSize*sprite.mGroupSize; i++) {
    int gpos = i / sprite.mFrameSize;
    int cpos = i%sprite.mFrameSize;
    Texture2D texture;
    texture.Generate2(sprite.mWidth, sprite.mHeight, (unsigned char*)&sprite.mFrames[gpos][cpos].src[0]);
    tSprit.push_back(texture);
  }
  
  mSprites.push_back(tSprit);
  /*读取武器Spirte*/
  tSprit.clear();
  NetEase::WDF wdf2(config.GetWdfPath("shape.wd3"));

  s = config.mDict["shape.wd3"][0];
  sscanf(s.c_str(),"%x",&id);
  sprite2 = wdf2.LoadSprite(id);
  for (int i = 0; i<sprite2.mFrameSize*sprite2.mGroupSize; i++) {
    int gpos = i / sprite2.mFrameSize;
    int cpos = i%sprite2.mFrameSize;

    Texture2D texture;
    texture.Generate2(sprite2.mWidth, sprite2.mHeight, (unsigned char*)&sprite2.mFrames[gpos][cpos].src[0]);
    tSprit.push_back(texture);
  }
  mSprites.push_back(tSprit);

  frame_count = sprite.mFrameSize;

  
//  mMoveList = mGameMap->Move(252, 60, 38, 16);
  
  cur_x = 1000;
  cur_y = 500;
}
//printf("%lf %lf %lf %lf\n", sx, sy, ex, ey);


double Astar_GetDistance(double sx, double sy, double ex, double ey)
{
  double dx = sx - ex;
  double dy = sy - ey;
  return sqrt(pow(dx,2) + pow(dy,2));
}

double Astar_GetAngle(double sx, double sy, double ex, double ey)
{
  double dx = ex - sx;
  double dy = ey - sy;
  double angle;
  double degree;
  angle = atan(dy / dx);
  degree = RadianToDegree(angle);
  if (dx < 0 && dy >= 0) {
    degree += 180;
  }
  else if (dx <=0 && dy<0) {
    degree += 180;
  }
  else if (dx > 0 && dy <0) {
    degree += 360;
    
  }
  else if (dx>=0 && dy>=0) {

  }
  return degree;
}

int Astar_GetDir(double degree) {
  //右下，左下，左上，右上，下，左，上，右
  // 0    1    2    3   4  5   6  7
  //  2 3 0 1       6 7   4 5
  //int innerDirs[8] = { 7,3,6,2,5,1,4,0 };
  int innerDirs[8] = { 7,0,4,1,5,2,6,3};
  if (360 - 22.5 <= degree || degree < 22.5) {
    return innerDirs[0];
  }
  else {
    for (int i = 1; i < 8; i++) {
      if (i * 45 - 22.5 <= degree && degree < i * 45 + 22.5) {
        return innerDirs[i];
      }
    }
    return innerDirs[0];
  }
}

int cnt = 0;
GLfloat delta2=0;
bool draw_cell = false;
void Game::Update(GLfloat dt)
{
  delta += dt;
  delta2 += dt;
  draw_cell = false;
  if (delta2 >= 4 * dt) {
    delta2 = 0;
    draw_cell = true;
    cur_frame++;
    if (cur_frame >= frame_count) {
      cur_frame = 0;
      
    }
  }
  if (delta >= dt) {
    cnt++;
    delta = 0;
    if (bmove) {
      if (!mMoveList.empty())
      {
        double local_velocity = move_velocity*dt;
        Pos d = mMoveList.front();
        dest.x = d.x * 20 + 10;
        dest.y = d.y * 20 + 10;
        if (Astar_GetDistance(cur_x, cur_y, dest.x, dest.y) > local_velocity) {
          double degree = Astar_GetAngle(cur_x, cur_y, dest.x, dest.y);
          dir = Astar_GetDir(degree);

          step_range_x = cos(DegreeToRadian(degree));
          step_range_y = sin(DegreeToRadian(degree));

          cur_x += step_range_x * local_velocity;
          cur_y += step_range_y*local_velocity;
        }
        else {
          Pos d = mMoveList.front();
          cur_x = d.x * 20 + 10;
          cur_y = d.y * 20 + 10;
          mMoveList.pop_front();
        }

      }
      else {
        
        bmove = false;
      }
    }
    else {

    }
    

  }
    
}

void Game::mouse_button_click()
{
  //printf("%lf %lf clicked!\n",mouse_x,mouse_y );
  // player_dest_x=mouse_x;
  // player_dest_y=mouse_y;
  bmove = false;
  mMoveList.clear();
  int mapOffsetX = 320 + sprite.mWidth / 2 - cur_x;
  int mapOffsetY = 240 + sprite.mHeight / 2 - cur_y;

  mMoveList = mGameMap->Move(cur_x/20, cur_y/20, (-mapOffsetX+mouse_x)/20,
    (-mapOffsetY + mouse_y)/20);
  bmove = true;
}
void Game::ProcessInput(GLfloat dt)
{


  // Move playerboard
  if (this->Keys[GLFW_KEY_A])
  {
    cur_x -= 3;
    // if(src_x<=-m_MapWidth+1024)src_x=-m_MapWidth+1024;
  }
  if (this->Keys[GLFW_KEY_D])
  {
    cur_x += 3;
    // if(src_x>=0)src_x=0;

  }

  if (this->Keys[GLFW_KEY_W])
  {
    cur_y -= 3;
    // if(src_y<=-m_MapHeight+768)src_y=-m_MapHeight+768;
  }

  if (this->Keys[GLFW_KEY_S])
  {
    cur_y += 3;
    // if(src_y>=0)src_y=0;

  }


}

void Game::Render()
{


  int mapOffsetX = 320 + sprite.mWidth / 2 - cur_x;
  int mapOffsetY =  240 + sprite.mHeight / 2 - cur_y;
  mGameMap->Draw(Renderer,mapOffsetX,mapOffsetY);
  

  int px =this->Width/2 - sprite.mWidth/2 ;
  int py =this->Height/2 - sprite.mHeight/2;
  
  int gpos = cur_frame / frame_count;
  int cpos = cur_frame%frame_count;
  Sprite2::Sequence& frame1 = sprite.mFrames[gpos][cpos];
  Sprite2::Sequence& frame2 = sprite2.mFrames[gpos][cpos];

  Renderer->DrawSprite(mSprites[0][cur_frame + dir*frame_count],
    glm::vec2(px, py),
    glm::vec2(sprite.mWidth, sprite.mHeight), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

  
  int px2 = px - (sprite2.mKeyX - sprite.mKeyX);  
  int py2 = py - (sprite2.mKeyY - sprite.mKeyY);
  
  Renderer->DrawSprite(mSprites[1][cur_frame + dir*frame_count],
    glm::vec2(px2, py2),
    glm::vec2(sprite2.mWidth, sprite2.mHeight),
    0.0f, 
    glm::vec3(1.0f, 1.0f, 1.0f));

  
  mapOffsetX = 320 + sprite.mWidth / 2 - cur_x;
  mapOffsetY =  240 + sprite.mHeight / 2 - cur_y;
  mGameMap->DrawMask(Renderer, mapOffsetX, mapOffsetY);
  //mGameMap->DrawCell(Renderer, mapOffsetX, mapOffsetY);

}