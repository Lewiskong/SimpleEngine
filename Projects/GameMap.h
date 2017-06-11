#pragma once
#include "../defines.h"
#include "../ThirdParty/NetEase/MAP.h"
#include "../SpriteRenderer.h"
#include "Heap.h"
#include "Astar.h"

#include <list>
#include "mhxy.h"
#include "../image.h"
/*
游戏地图类的封装
*/
class GameMap
{
public:
	GameMap(std::string filename);
	~GameMap();
	std::list<Pos> Move(int sx, int sy, int ex, int ey);
	NetEase::MAP* GetMapPtr();
	void clamp(int val, int min, int max);
	Astar* GetAstar() { return mAstar; };
	int GetRowCount() { return mRow; };
	int GetColCount() { return mCol; };
	void Draw(SpriteRenderer* renderer, int offx, int offy);
	void DrawMask(SpriteRenderer* renderer, int offx, int offy);
	void DrawCell(SpriteRenderer* renderer, int cur_x, int cur_y);
private:
	std::vector<Texture *> mMapTiles;
	std::vector<Texture *> mMaskTiles;
	// Texture mCellPic;
	int mWidth;
	int mHeight;
	int mMapWidth;
	int mMapHeight;
	int mCellWidth;
	int mCellHeight;
	int** mCell;
	int mRow;
	int mCol;
	NetEase::MAP* mXyqMap;
	Astar* mAstar;

};


