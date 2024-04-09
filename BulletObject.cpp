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
	rect_.x = x_val;
	rect_.y = y_val;
	if (rect_.x > x_border)
	{
		in_screen = false;
	}
}