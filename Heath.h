#pragma once
#ifndef HEALTH_H
#define HEALTH_H
#include"Base.h"
#include"CommonFunction.h"
class Health:public BaseObject
{
public:
	Health();
	~Health();
	int max_health;
	int max_width;
	int curren_health;
	int curren_width;
	int max_height;
	void TakeDamage(int damge);
	void Update(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des, const SDL_Rect* clip = NULL);
protected:
	
};



#endif