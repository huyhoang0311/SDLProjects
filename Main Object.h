#pragma once
#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#define NUM_FRAME 8
using namespace std;
#include<vector>
#include"BulletObject.h"
#include"Base.h"
#include"CommonFunction.h"
class MainObject :public BaseObject
{
public:MainObject(); 
	  ~MainObject();
	  enum Walktype
	  {
		  walk_right = 0,
		  walk_left = 1,
	  };
	  void LoadIMG(SDL_Renderer* screen);
	  void Show(SDL_Renderer* des);
	  void HandleInputEvents(SDL_Event events, SDL_Renderer* screen);
	  void set_clip();


	  void DoPlayer(Map& map_data);
	  void CheckToMap(Map& map_data);

	  void SetMapXY(const int map_x, const int map_y)
	  {
		  map_x_ = map_x;
		  map_y_ = map_y;
	  }
	  void CenterEntityOnMap(Map& map_data);

	  void set_bullet_list(vector<BulletObject*> bullet_list)
	  {
		 p_bullet_list = bullet_list;
	  }
	  vector<BulletObject*> get_bullet_list() const
	  {
		  return p_bullet_list;
	  }
	  void HandleBullet(SDL_Renderer* des);

	  void RemoveBullet(const int& idx);
	  
	
	  float get_x_pos();
	  float get_y_pos();
	  int get_width_frame();
	  int get_height_frame();

	  bool normalise;
	  bool able_to_demon;
	  int lastShotTime;
	  int CurrentShotTime;
	  int special_shot;




	  float x_pos;
	  float y_pos;


private:

	vector<BulletObject*> p_bullet_list;

	float x_val;
	float y_val;





	SDL_Texture* p_object_left;
	SDL_Texture* p_object_right;
	SDL_Texture* demon_mode_left;
	SDL_Texture* demon_mode_right;

	int width_frame;
	int height_frame;

	

	SDL_Rect frame_clip_[NUM_FRAME*2];


	Input input_type_;

	int frame_;



	int status_;


	bool on_ground_;

	int map_x_, map_y_;




};






#endif 



