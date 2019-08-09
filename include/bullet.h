#pragma once
#include <SDL2/SDL.h>
class bullet
{
  public:
    bullet();
    void setPosition(double x, double y);
    double getX();
    double getY();
    void updatePosition();
    void draw(SDL_Renderer *renderer);
    double getDamage();
  private:
    double xcoord;
    double ycoord;
    double damage;
};
