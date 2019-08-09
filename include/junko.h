#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class junko
{
  public:
    junko();
    ~junko();
    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
    int getX();
    int getY();
    void updateX(double dx);
    int updateHp();
  private:
    int x;
    int y;
    int health;
};
