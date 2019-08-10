#pragma once
#include <gamelogic.h>
class star
{
  public:
    //constructor/deconstructor

    star();
    ~star();
    //setters

    void setPosition(int x, int y);
    //misc

    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
  private:
    int xcoord;
    int ycoord;
};

