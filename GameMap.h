#pragma once

#ifndef GAME_MAP_H
#define GAME_MAP_H

#include"CommonFunction.h"
#include"Base.h"

#define MAX_TILE_ 20


class TileMat : public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};
class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }

	void loadMap(const char* name);
	void LoadTiles(SDL_Renderer*screen);
	void Drawmap(SDL_Renderer* screen);
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE_];

};




#endif