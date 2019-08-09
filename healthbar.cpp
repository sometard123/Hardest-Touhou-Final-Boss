#include <healthbar.h>
#include <iostream>
using namespace std;
void healthbar::setPosition(double x, double y)
{
  this->xcoord = x;
  this->ycoord = y;
}

void healthbar::draw(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0);
  SDL_Rect healthBarRect = {(int)xcoord, (int)ycoord, 1, 20};
  SDL_RenderFillRect(renderer, &healthBarRect);
}
