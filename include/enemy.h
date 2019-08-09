#pragma once
#include <SDL2/SDL.h>
class enemy
{
  public:
    enemy(double xcoord, double ycoord, double deltax, double deltay);
    double getX();
    double getY();
    void updatePosition();
    void draw(SDL_Renderer *renderer);
  private:
    double health;
    double x;
    double y;
    double dx;
    double dy;
};
