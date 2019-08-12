#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class junko {
  public:
    //constructor/deconstructor

    junko();
    ~junko();
    //setters and getters

    int getX();
    int getY();
    //other member functions

    void updateX(double dx);
    int updateHp();
    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
  private:
    int x;
    int y;
    int health;
};
