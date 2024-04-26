
#include"Player2.h"
#include"BulletObject.h"

using namespace std;
#define BULLET_SPEED 20
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 10
#define PLAYER_SPEED 20
#define PLAYER_JUMP_VAL 12



#define BLANK_TILE 0


MainObject2::MainObject2()
{
	frame_ = 0;
	x_pos = 1100;
	y_pos = 0;
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	status_ = 1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	on_ground_ = false;
	normalise = true;
	able_to_demon = false;
	lastShotTime = 0;
	CurrentShotTime = 0;
	map_x_ = 0;
	map_y_ = 0;
}
MainObject2::~MainObject2()
{

}
void MainObject2::LoadIMG( SDL_Renderer* screen)
{
	string path_left, path_right,demon_left,demon_right;
	path_left = "Character/DemonSpiderWalkLeft.png";
	SDL_Texture* new_texture_ = NULL;
	SDL_Surface* load_surface = IMG_Load(path_left.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture_ = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture_ != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_left = new_texture_;

	path_right =  "Character/DemonSpiderWalk.png";
	load_surface = IMG_Load(path_right.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture_ = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture_ != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object_right = new_texture_;


	demon_left = "Character/AngelOfDeathFlyLeft.png";

	SDL_Texture* demon_texture_ = NULL;
	SDL_Surface* demon_surface = IMG_Load(demon_left.c_str());
	if (demon_surface != NULL)
	{
		SDL_SetColorKey(demon_surface, SDL_TRUE, SDL_MapRGB(demon_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		demon_texture_ = SDL_CreateTextureFromSurface(screen, demon_surface);
		if (demon_texture_ != NULL)
		{
			rect_.w = demon_surface->w;
			rect_.h = demon_surface->h;
		}
		SDL_FreeSurface(demon_surface);
	}
	demon_mode_left = demon_texture_;

	demon_right = "Character/AngelOfDeathFly.png";
	demon_surface = IMG_Load(demon_right.c_str());
	if (demon_surface != NULL)
	{
		SDL_SetColorKey(demon_surface, SDL_TRUE, SDL_MapRGB(demon_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		demon_texture_ = SDL_CreateTextureFromSurface(screen, demon_surface);
		if (demon_texture_ != NULL)
		{
			rect_.w = demon_surface->w;
			rect_.h = demon_surface->h;
		}
		SDL_FreeSurface(demon_surface);
	}
	demon_mode_right = demon_texture_;

	width_frame = rect_.w /NUM_FRAME_2;
	height_frame = rect_.h;
}
void MainObject2::set_clip()
{
	if (width_frame > 0 && height_frame > 0)
	{

		for (int i = 0; i < NUM_FRAME_2; ++i)
		{
			frame_clip_[i].x = i * width_frame;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame;
			frame_clip_[i].h = height_frame;

		}
	}
}

void MainObject2::Show(SDL_Renderer* des)
{
	if (input_type_.left_ == 1 || input_type_.right_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}
	if (frame_ >= NUM_FRAME_2)
	{
		frame_ = 0;
	}

	rect_.x = x_pos - map_x_;
	rect_.y = y_pos - map_y_;
	SDL_Rect* current_clip = &frame_clip_[frame_];
	SDL_Rect  renderQuad = { rect_.x, rect_.y, width_frame, height_frame };

	if (normalise == true)
	{
		if (status_ == walk_left)
		{
			SDL_RenderCopy(des, p_object_left, current_clip, &renderQuad);
		}
		else
		{
			SDL_RenderCopy(des, p_object_right, current_clip, &renderQuad);
		}
	}
	else 
	{
		if (status_ == walk_left)
		{
			SDL_RenderCopy(des, demon_mode_left, current_clip, &renderQuad);
		}
		else
		{
			SDL_RenderCopy(des, demon_mode_right, current_clip, &renderQuad);
		}

	}
}

void MainObject2::HandleInputEvents(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			status_ = walk_right;
			input_type_.right_ = 1;
			input_type_.left_ = 0;
		}
		break;
		case SDLK_LEFT:
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
		case SDLK_RIGHT:
		{
			input_type_.right_ = 0;
		}
		break;
		case SDLK_LEFT:
		{
			input_type_.left_ = 0;
		}
		break;
		}
	}

	//special skill
	if (events.type == SDL_KEYDOWN)
	{
		if (events.key.keysym.sym == SDLK_KP_2)
		{
			if (rect_.y >= 50) { input_type_.jump_ = 1; }
		}
		if (events.key.keysym.sym == SDLK_KP_1)
		{
			CurrentShotTime = SDL_GetTicks();
			if (lastShotTime == 0 || CurrentShotTime >= lastShotTime + 500)
			{
				lastShotTime = CurrentShotTime;
				BulletObject* p_bullet = new BulletObject();
				p_bullet->loadImg("Bullet/Bullet.png", screen);
				if (status_ == walk_left)
				{
					p_bullet->loadImg("Bullet/Bullet_left.png", screen);
					p_bullet->get_bullet_dir(DIR_LEFT);
					p_bullet->set_bullet_dir(DIR_LEFT);
					p_bullet->SetRect(rect_.x - 50, rect_.y - 10);
				}
				else
				{
					p_bullet->get_bullet_dir(DIR_RIGHT);
					p_bullet->set_bullet_dir(DIR_RIGHT);
					p_bullet->SetRect(rect_.x + 50, rect_.y - 10);
				}

				p_bullet->set_x_val(BULLET_SPEED);
				//p_bullet->set_y_val(40);
				p_bullet->set_in_screen(true);
				p_bullet_list_2.push_back(p_bullet);
			}
		}
		if (events.key.keysym.sym == SDLK_KP_4)
		{
			if (normalise == false)
			{
				int range = rand() % 251 + 200;
				BulletObject* sky_bullet = new BulletObject();
				sky_bullet->loadImg("Bullet/05.png", screen);
				sky_bullet->get_bullet_dir(DIR_DOWN);
				sky_bullet->set_bullet_dir(DIR_DOWN);
				sky_bullet->SetRect(rect_.x - range, 0);
				sky_bullet->set_y_val(20);
				sky_bullet->set_in_screen(true);
				p_bullet_list_2.push_back(sky_bullet);
				BulletObject* sky_bullet_2 = new BulletObject();
				sky_bullet_2->loadImg("Bullet/05.png", screen);
				sky_bullet_2->get_bullet_dir(DIR_DOWN);
				sky_bullet_2->set_bullet_dir(DIR_DOWN);
				sky_bullet_2->SetRect(rect_.x + range, 0);
				sky_bullet_2->set_y_val(20);
				sky_bullet_2->set_in_screen(true);
				p_bullet_list_2.push_back(sky_bullet_2);
			}
	
		}
		if (events.key.keysym.sym == SDLK_KP_3)
		{
			if (able_to_demon == true)
			{
				normalise = false;
			}
		}
	}

}
void MainObject2::HandleBullet(SDL_Renderer* des)
{
	int num_ = p_bullet_list_2.size();
	for (int i = 0; i < num_; ++i)
	{
		BulletObject* p_bullet = p_bullet_list_2.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_in_screen() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des); 
			}
			else
			{
				p_bullet = NULL;

			}
		}
	}

}


void MainObject2::DoPlayer(Map& map_data_)
{
	x_val = 0;
	y_val += GRAVITY_SPEED;
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

	if (input_type_.jump_ == 1)
	{
		y_val = -PLAYER_JUMP_VAL;
		input_type_.jump_ = 0;

	}



	CheckToMap(map_data_);
	//CenterEntityOnMap(map_data_);
}

void MainObject2::CenterEntityOnMap(Map& map_data)
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
		map_data.start_y = map_data.max_y_ - SCREEN_HEIGHT;
	}
}
void MainObject2::CheckToMap(Map& map_data)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//Check horizontal
	int height_min = min(height_frame, TILE_SIZE);
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame - 1) / TILE_SIZE;
	y1 = (y_pos) / TILE_SIZE;
	y2 = (y_pos + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y)
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
void MainObject2::RemoveBullet(const int& idx)
{
	int size = p_bullet_list_2.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bullet_list_2.at(idx);
		p_bullet_list_2.erase(p_bullet_list_2.begin() + idx);
		if (p_bullet != NULL)
		{
			
			p_bullet = NULL;
		}
	}
}


float MainObject2::get_x_pos()
{
	return rect_.x;
}
float MainObject2::get_y_pos()
{
	return rect_.y;
}
int MainObject2::get_height_frame()
{
	return height_frame;
}
int MainObject2::get_width_frame()
{
	return width_frame;
}