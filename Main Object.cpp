#include"Main Object.h"
using namespace std;

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 2



#define BLANK_TILE 0


MainObject::MainObject()
{
	frame_ = 0;
	x_pos = 0;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
}
MainObject::~MainObject()
{

}
bool MainObject::LoadIMG(string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::loadImg(path, screen);
	if (ret == true)
	{
		width_frame = rect_.w / 8;
		height_frame = rect_.h;
	}
	return ret;
}
void MainObject::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{
		
		for (int i = 0; i <= 7; ++i)
		{
			frame_clip_[i].x = i * width_frame;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame;
			frame_clip_[i].h = height_frame;

		}


	}
}

void MainObject::Show(SDL_Renderer* des)
{
	if (status_ == walk_left)
	{
		LoadIMG("Character/player_left.png", des);
	}
	else
	{
		LoadIMG("Character/player_right.png", des);
	}

	if (input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if (frame_ >= 8)
	{
		frame_ = 0;
	}

	rect_.x = x_pos - map_x_;
	rect_.y = y_pos - map_y_;
	SDL_Rect *current_clip = &frame_clip_[frame_];
	SDL_Rect  renderQuad = { rect_.x, rect_.y, width_frame, height_frame };
	SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
}

void MainObject::HandleInputEvents(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			status_ = walk_right;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
		}
		break;
		case SDLK_a:
		{
			status_ = walk_left;
			input_type_.left_ = 1;
			input_type_.right_ = 0;
		}
		break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{

			input_type_.right_ = 0;
		}
		break;
		case SDLK_a:
		{
			input_type_.left_ = 0;
		}
		break;
		}
	}
}


void MainObject::DoPlayer(Map& map_data_)
{
	x_val = 0;
	y_val+=GRAVITY_SPEED;
	if (y_val >= MAX_FALL_SPEED)
	{
		y_val = MAX_FALL_SPEED;
	}
	if (input_type_.left_ == 1)
	{
		x_val -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1)
	{
		x_val += PLAYER_SPEED;
	}
	CheckToMap(map_data_);
	CenterEntityOnMap(map_data_);
}

void MainObject::CenterEntityOnMap(Map& map_data)
{
	map_data.start_x = x_pos - (SCREEN_WIDTH / 2);
	if (map_data.start_x < 0)
	{
		map_data.start_x = 0;
	}
	else if (map_data.start_x + SCREEN_WIDTH > map_data.max_x_)
	{
		map_data.start_x = map_data.max_x_ - SCREEN_WIDTH;
	}
	map_data.start_y = y_pos - (SCREEN_HEIGHT / 2);
	if (map_data.start_y < 0)
	{
		map_data.start_y = 0;
	}
	else if (map_data.start_y + SCREEN_HEIGHT >= map_data.max_y_)
	{
		map_data.start_y = map_data.max_y_-SCREEN_HEIGHT;
	}
}
void MainObject::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;
	
	int y1 = 0;
	int y2 = 0;

	//Check horizontal
	int height_min = min(height_frame,TILE_SIZE);
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame-1) / TILE_SIZE;
	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && y2 <= MAX_MAP_Y)
	{
		if (x_val > 0)
		{
			if (map_data.tile[y1][x2] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				x_pos = x2 * TILE_SIZE;
				x_pos -= width_frame + 1;
				x_val = 0;
			}
		}
		else if (x_val < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y2][x1] != BLANK_TILE)
			{
				x_pos = (x1 + 1) * TILE_SIZE;
				x_val = 0;
			}
		}
	}
	//Check vertical
	int width_min = min(width_frame, TILE_SIZE);
	x1 = (x_pos) / TILE_SIZE;
	x2 = (x_pos + width_min) / TILE_SIZE;

	y1 = (y_pos + x_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame - 1) / TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
	{
		if (y_val > 0)
		{
			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE)
			{
				y_pos = y2 * TILE_SIZE;
				y_pos -= (height_frame + 1);
				y_val = 0;
				on_ground_ = true;
			}
		}
		else if (y_val < 0)
		{
			if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE)
			{
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
	}
	x_pos += x_val;
	y_pos += y_val;
	if (x_pos < 0)
	{
		x_pos = 0;
	}
	else if (x_pos + width_frame > map_data.max_x_)
	{
		x_pos = map_data.max_x_ - width_frame - 1;
	}
	

}