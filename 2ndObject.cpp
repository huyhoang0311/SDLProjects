#include"Main Object.h"
using namespace std;

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 8



#define BLANK_TILE 0

MainObject::MainObject()
{
	frame_2 = 0;
	x_pos_2 = SCREEN_WIDTH-10;
	y_pos_2 = 0;
	x_val_2 = 0;
	y_val_2 = 0;
	width_frame_2 = 0;
	height_frame_2 = 0;
	status_ = -1;
	input_type_2.left_ = 0;
	input_type_2.right_ = 0;
	input_type_2.up_ = 0;
	input_type_2.down_ = 0;

}
MainObject::~MainObject()
{

}
bool MainObject::LoadIMG(string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == true)
	{
		width_frame_2 = rect_.w / 8;
		height_frame_2 = rect_.h;
	}
	return ret;
}
void MainObject::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{

		for (int i = 0; i <= 7; ++i)
		{
			frame_clip_2[i].x = i * width_frame;
			frame_clip_2[i].y = 0;
			frame_clip_2[i].w = width_frame;
			frame_clip_2[i].h = height_frame;
		}
	}
}
void MainObject::Show(SDL_Renderer* des)
{
	if (status_2 == walk_left)
	{
		LoadIMG("Character/2.png", des);
	}
	else
	{
		LoadIMG("Character/1.png", des);
	}

	if (input_type_2.left_ == 1 || input_type_2.right_ == 1)
	{
		frame_2++;
	}
	else
	{
		frame_2 = 0;
	}
	if (frame_2 >= 8)
	{
		frame_2 = 0;
	}

	//rect_.x = x_pos - map_x_;
	//rect_.y = y_pos - map_y_;
	SDL_Rect* current_clip = &frame_clip_2[frame_2];
	SDL_Rect  renderQuad = { rect_.x, rect_.y, width_frame_2, height_frame_2 };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}