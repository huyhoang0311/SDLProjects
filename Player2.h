#pragma once
#ifndef PLAYER2_OBJECT_H
#define PLAYER2_OBJECT_H
#include"Base.h"
#include"CommonFunction.h"
class MainObject2 :public BaseObject
{
public:MainObject2();
	  ~MainObject2();
	  enum Walktype
	  {
		  walk_right = 0,
		  walk_left = 1,
	  };
	  virtual bool LoadIMG(std::string path, SDL_Renderer* screen);
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
private:
	float x_val;
	float y_val;


	float x_pos;
	float y_pos;







	int width_frame;
	int height_frame;




	SDL_Rect frame_clip_[8];


	Input input_type_;

	int frame_;



	int status_;


	bool on_ground_;

	int map_x_, map_y_;
};






#endif 
