#pragma once
#include <SDL_stuff.h>
class healthbar {
  public:
    //constructor and deconstructor

    healthbar();
    ~healthbar();
    //setters

    void setPosition(double x, double y);
    //misc

    void draw(SDL_Renderer *renderer);
  private:
    double xcoord;
    double ycoord;
};

