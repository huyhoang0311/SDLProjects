#include"GameMap.h"
#include"CommonFunction.h"
#include"Main Object.h"
#include"Base.h"
#include"Player2.h"
#include"Timer.h"
#include"Heath.h"
using namespace std;

BaseObject g_Background;
int type_menu = 0;
bool is_quit = false;





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
	
	bool ret = g_Background.loadImg("images/OIG3.jpg",gScreen);
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

bool check_mouse_vs_item(const int& x, const int& y, const SDL_Rect& rect) 
{
	if (x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h) {
		return true;
	}
	return false;
}




void ShowMenu(SDL_Renderer* screen) {
	BaseObject menu;
	if (!menu.loadImg("images/menu.jpg", screen)) {
		is_quit = true;
		return;
	}

	BaseObject list_menu[8];
	list_menu[0].loadImg("images/playbutton.png", gScreen);
	list_menu[1].loadImg("images/replaybutton.png", gScreen);
	list_menu[2].loadImg("images/exitbutton.png", gScreen);
	list_menu[3].loadImg("images/playbutton1.png", gScreen);
	list_menu[4].loadImg("images/replaybutton1.png",gScreen);
	list_menu[5].loadImg("images/exitbutton1.png",gScreen);
	list_menu[6].loadImg("images/Player 1 win.png", gScreen);
	list_menu[7].loadImg("images/Player 2 win.png", gScreen);
	

	list_menu[0].SetRect(355, 300);
	list_menu[1].SetRect(355, 300);
	list_menu[2].SetRect(355, 370);
	list_menu[3].SetRect(345, 297);
	list_menu[4].SetRect(345, 297);
	list_menu[5].SetRect(345, 367);
	list_menu[6].SetRect(0, 0);
	list_menu[7].SetRect(0, 0);


	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_Event) != 0) {


			menu.Render(gScreen);
			if (type_menu == 0) {
				list_menu[0].Render(gScreen);
				list_menu[2].Render(gScreen);
			}
			else if (type_menu == 1) 
			{
				list_menu[6].Render(gScreen);

				list_menu[1].Render(gScreen);
				list_menu[2].Render(gScreen);
			}
			else if (type_menu == 2)
			{
				list_menu[7].Render(gScreen);

				list_menu[1].Render(gScreen);
				list_menu[2].Render(gScreen);
			}


			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (g_Event.type == SDL_QUIT) {
				quit = true;
				is_quit = true;
			}


			else if (g_Event.type == SDL_MOUSEMOTION) {

				for (int i = 0; i < 3; i++) {
					if (check_mouse_vs_item(mouseX, mouseY, list_menu[i].GetRect())) {
						if (i == 0 && type_menu == 0) list_menu[3].Render(gScreen);
						else if (i == 1 && type_menu == 1) list_menu[4].Render(gScreen);
						else if (i == 2) list_menu[5].Render(gScreen);
					}
				}
			}

			if (g_Event.type == SDL_MOUSEBUTTONDOWN) {

				if (g_Event.button.button == SDL_BUTTON_LEFT) {
					for (int i = 3; i < 6; i++) {
						if (check_mouse_vs_item(mouseX, mouseY, list_menu[i].GetRect())) {
							if (i == 3 || i == 4) { quit = true; }
							else if (i == 5) { is_quit = true; quit = true; }
						}
					}
				}


			}

		}
		SDL_RenderPresent(gScreen);
	}

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


	Health *health_bar=new Health();
	health_bar->loadImg("Health/empty health bar.png", gScreen);
	health_bar->SetRect(0, 0);





	Health *health_ = new Health();
	health_->loadImg("Health/Health.png", gScreen);
	health_->SetRect(0, 0);


	Health* health_bar_2 = new Health();
	health_bar_2->loadImg("Health/empty health bar.png", gScreen);
	health_bar_2->SetRect(850, 0);
	Health* health_2 = new Health();
	health_2->loadImg("Health/Health_2.png", gScreen);
	health_2->SetRect(850, 0);



	

	ShowMenu(gScreen);
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

		health_bar->Show(gScreen);
		health_->Update(gScreen);

		health_bar_2->Show(gScreen);
		health_2->Update(gScreen);


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

				bool check1 = CommonFunction::CheckCollision(bullet_Rect, p1Rect);
				if (check1)
				{
					player2.RemoveBullet(r);
					health_->TakeDamage(5);
					
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

				bool check2 = CommonFunction::CheckCollision( bullet_Rect_1, p2Rect );
				if (check2)
				{
					
					player.RemoveBullet(r);
					health_2->TakeDamage(10);
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


		if (health_->curren_health <= 0.5 * health_->max_health)
		{
			player.able_to_demon = true;
		}
		if (health_2->curren_health <= 0.5 * health_2->max_health)
		{
			player2.able_to_demon = true;
		}

		if (health_->curren_health <= 0 )
		{
			health_->curren_health = health_->max_health;
			health_2->curren_health = health_2->max_health;
			player.x_pos = 0;
			player2.x_pos = 1100;

			type_menu = 2;
			ShowMenu(gScreen);
		}
		if (health_2->curren_health <= 0)
		{
			health_->curren_health = health_->max_health;
			health_2->curren_health = health_2->max_health;
			player.x_pos = 0;
			player2.x_pos = 1100;
			
			type_menu = 1;
			ShowMenu(gScreen);

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
