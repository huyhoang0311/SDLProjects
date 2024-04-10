#include"GameMap.h"
#include"CommonFunction.h"
#include"Main Object.h"
#include"Base.h"
#include"Player2.h"
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


		SDL_RenderPresent(gScreen);

	}
	close();
	 return 0;
}
