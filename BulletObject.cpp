#include"BulletObject.h"
BulletObject::BulletObject()
{
	x_val = 0;
	y_val = 0;
	in_screen = false;

}
BulletObject::~BulletObject()
{

}
void BulletObject::HandleMove(const int& x_border, const int& y_border)
{

	if (bullet_dir == DIR_RIGHT)
	{
		rect_.x += x_val;
		if (rect_.x > x_border)
		{
			in_screen = false;
		}
	}
	else if(bullet_dir==DIR_LEFT)
	{
		rect_.x -= x_val;
		if (rect_.x < 0)
		{
			in_screen = false;
		}
	}
	else if (bullet_dir = DIR_DOWN)
	{
		rect_.y += y_val;
		if (rect_.y >= y_border)
		{
			in_screen = false;
		}
	}

}