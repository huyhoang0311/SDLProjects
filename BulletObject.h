#pragma once
#ifndef  BULLET_OBJECT_H
#define BULLET_OBJECT_H
#include"Base.h"
#include"CommonFunction.h"

class BulletObject:public BaseObject
{
public:
	BulletObject();
	~BulletObject();

	void set_x_val(const int& xVal)
	{
		x_val = xVal;
	}
	void set_y_val(const int& yVal)
	{
		y_val = yVal;
	}
	void set_in_screen(const bool& inscreen)
	{
		in_screen = inscreen;
	}
	bool get_in_screen() const
	{
		return in_screen;
	}
	void HandleMove(const int& x_border, const int& y_border);

private:
	int x_val;
	int y_val;
	bool in_screen;
};




#endif 
