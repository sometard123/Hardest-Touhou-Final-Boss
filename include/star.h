#pragma once
#include <gamelogic.h>
class star
{
  public:
    void setPosition(int x, int y);
    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
  private:
    int xcoord;
    int ycoord;
};

