#pragma once
#include <gamelogic.h>
class healthbar
{
  public:
    void setPosition(double x, double y);
    void draw(SDL_Renderer *renderer);
  private:
    double xcoord;
    double ycoord;
};

