#include"GameMap.h"
#include"CommonFunction.h"
#include"Base.h"
using namespace std;

BaseObject g_Background;


bool InitData()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	gWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
	bool ret = g_Background.loadImg("BackGround.jpg",gScreen);
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
	game_map.loadMap("map01.dat");
	game_map.LoadTiles(gScreen);
	bool is_quit = false;
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_Event) != 0)
		{
			if (g_Event.type == SDL_QUIT)
			{
				is_quit = true;
			}
		}
		SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gScreen);



		g_Background.Render(gScreen, NULL);
		game_map.Drawmap(gScreen);


		SDL_RenderPresent(gScreen);
	}
	close();



	 
	 return 0;
}

/*#include"CommonFunction.h"
using namespace std;




//initialize surface of the window
SDL_Surface* gScreenSurface = NULL;



//initialize Renderer
SDL_Renderer* gRenderer = NULL;
//initialize Texture
SDL_Texture* Imagetext = NULL;

//create window
bool init()
{
	bool success = true;
	gWindow = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gRenderer = SDL_CreateRenderer(gWindow, -1, 0);

	return success;
}

bool loadMedia()
{
	bool success = true;
	gScreenSurface = IMG_Load("C:/Users/ADMIN/source/repos/SDLProjects/BackGround.jpg");
	Imagetext = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
	SDL_RenderCopy(gRenderer, Imagetext, NULL, NULL);
	SDL_RenderPresent(gRenderer);
	return success;
}
void close()
{
	//Deallocate surface
	SDL_FreeSurface(gScreenSurface);
	gScreenSurface = NULL;
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	//Quit SDL subsystems
	SDL_Quit();

}
int main(int argc, char* argv[])
{
	if (!init())
	{
		cout << "error to init";
	}
	else
	{
		if (!loadMedia())
		{
			cout << "error to load media";
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {


					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}


			}

		}
	}

	close();

	return 0;
}

*/