#include"Base.h"
#include"CommonFunction.h"
#include"Heath.h"
Health::Health()
{
	max_health = 100;
	max_width = 400;
	curren_health = max_health;
	curren_width = max_width;
	max_height = 50;
	
}
Health::~Health()
{

}
void Health::TakeDamage(int damage)
{
	curren_health -= damage;
}
bool Health::LoadImg(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* new_texture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL)
	{
		SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
		new_texture = SDL_CreateTextureFromSurface(screen, load_surface);
		if (new_texture != NULL)
		{
			rect_.w = load_surface->w;
			rect_.h = load_surface->h;
		}
		SDL_FreeSurface(load_surface);
	}
	p_object = new_texture;
	return p_object != NULL;
}
void Health::Show(SDL_Renderer* des, const SDL_Rect* clip)
{
	
	SDL_Rect renderQuad = { rect_.x, rect_.y, max_width,max_height};
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
} 
void Health::Update(SDL_Renderer* des, const SDL_Rect* clip)
{
	curren_width = max_width * curren_health / max_health;
	SDL_Rect renderQuad = { rect_.x, rect_.y, curren_width,max_height };
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
}



