#include"GameMap.h"
#include"CommonFunction.h"
#include"Main Object.h"
#include"Base.h"
#include"Player2.h"
#include"Timer.h"
using namespace std;

BaseObject g_Background;


bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280,640, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
	{
		success = false;
	}
	else
	{
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gScreen == NULL) { return false; }
		else
		{
			SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlags = IMG_INIT_PNG;
			if (!IMG_Init(imgFlags)&&imgFlags)
			{
				success = false;
			}
		}
	}
	return success;
}

bool loadBackground()
{
	
	bool ret = g_Background.loadImg("OIG3.jpg",gScreen);
	if (ret == false)
	{
		return false;
	}
	return true;
}

void close()
{
	g_Background.Free();
	SDL_DestroyRenderer(gScreen);

}





int main(int argc, char* argv[])
{
	Timer fps_clock;







	if (InitData() == false)
	{
		return -1;
	}
	if (loadBackground() == false)
	{
		return -2;
	}
	GameMap game_map;
	game_map.loadMap("map/map01.dat");
	game_map.LoadTiles(gScreen);

	MainObject player;
	player.LoadIMG(gScreen);
	player.set_clip();


	MainObject2 player2;
	player2.LoadIMG(gScreen);
	player2.set_clip();

	bool is_quit = false;
	while (!is_quit)
	{
		fps_clock.start();
		while (SDL_PollEvent(&g_Event) != 0)
		{
			if (g_Event.type == SDL_QUIT)
			{
				is_quit = true;
			}

			
			player2.HandleInputEvents(g_Event, gScreen);
			player.HandleInputEvents(g_Event, gScreen);

		}
		SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gScreen);



		g_Background.Render(gScreen, NULL);
		


		Map map_data = game_map.getMap();


		player2.SetMapXY(map_data.start_x, map_data.start_y);
		player2.DoPlayer(map_data);
		player2.Show(gScreen);
		player2.HandleBullet(gScreen);

		player.HandleBullet(gScreen);
		player.SetMapXY(map_data.start_x, map_data.start_y);
		player.DoPlayer(map_data);
		player.Show(gScreen);

		



		game_map.SetMap(map_data);
		game_map.Drawmap(gScreen); 





		vector<BulletObject*> bullet_arr = player2.get_bullet_list();
		for (int r = 0; r<int(bullet_arr.size()); ++r)
		{
			BulletObject* p2_bullet = bullet_arr.at(r);
			if (p2_bullet != NULL)
			{
				SDL_Rect p1Rect;
				p1Rect.x = player.get_x_pos();
				p1Rect.y = player.get_y_pos();
				p1Rect.w = player.get_width_frame();
				p1Rect.h = player.get_height_frame();
				SDL_Rect bullet_Rect = p2_bullet->GetRect();

				bool check1 = CommonFunction::CheckCollision(p1Rect, bullet_Rect);
				if (check1)
				{
					player2.RemoveBullet(r);
					
				}
			}
		}
		vector<BulletObject*> bullet_arr_1 = player.get_bullet_list();
		for (int r = 0; r<int(bullet_arr_1.size()); ++r)
		{
			BulletObject* p1_bullet = bullet_arr_1.at(r);
			if (p1_bullet != NULL)
			{
				SDL_Rect p2Rect;
				p2Rect.x = player2.get_x_pos();
				p2Rect.y = player2.get_y_pos();
				p2Rect.w = player2.get_width_frame();
				p2Rect.h = player2.get_height_frame();
				SDL_Rect bullet_Rect_1 = p1_bullet->GetRect();

				bool check2 = CommonFunction::CheckCollision(p2Rect, bullet_Rect_1);
				if (check2)
				{
					player.RemoveBullet(r);
					
				}
			}
		}
		for (int ii = 0; ii<int(bullet_arr_1.size()); ++ii)
		{
			BulletObject* p1_bullet_ = bullet_arr_1.at(ii);
			for (int jj = 0; jj<int(bullet_arr.size()); ++jj)
			{
				BulletObject* p2_bullet_ = bullet_arr.at(jj);
				SDL_Rect bullet_Rect_a = p2_bullet_->GetRect();
				SDL_Rect bullet_Rect_b = p1_bullet_->GetRect();
				bool check3 = CommonFunction::CheckCollision(bullet_Rect_a, bullet_Rect_b);
				if (check3)
				{
					player.RemoveBullet(ii);
					player2.RemoveBullet(jj);
				}
			}
		}
		SDL_RenderPresent(gScreen);


		int real_time = fps_clock.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SEC;

		if (real_time < time_one_frame)
		{
			int delay_time = time_one_frame - real_time;
			SDL_Delay(delay_time);
		}
	}
	close();
	return 0;
}
