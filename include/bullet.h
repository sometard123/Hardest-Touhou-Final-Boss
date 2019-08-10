#pragma once
#include <SDL2/SDL.h>
class bullet
{
  public:
    //constructor/deconstructor

    bullet();
    ~bullet();
    //setters

    void setPosition(double x, double y);
    //getters

    double getX();
    double getY();
    double getDamage();
    //misc

    void updatePosition();
    void draw(SDL_Renderer *renderer);
  private:
    double xcoord;
    double ycoord;
    double damage;
};
