#ifndef COMMON_FUNCTION_H
#define  COMMON_FUNCTION_H
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <SDL_image.h>


static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event g_Event ;


//Timer
const int FRAME_PER_SEC = 25; //fps


//Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0XFF;



#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10



typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;
};





typedef struct Map
{
	int start_x;
	int start_y;
	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name;
};

#endif
