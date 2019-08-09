#include <junko.h>
#include <iostream>
using namespace std;
junko::junko()
{
  x = 330;
  y = 100;
  health = 2870;
}

junko::~junko()
{
}

int junko::getX()
{
  return x;
}

int junko::getY()
{
  return y;
}

void junko::updateX(double dx)
{
  x += dx;
}

int junko::updateHp()
{
  health--;
  return health;
}
  
void junko::draw(SDL_Renderer *renderer, SDL_Texture *texture)
{
  int w;
  int h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  w /= 4;
  h /= 4;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_Rect JunkoRect = {x- 49, y - 62, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &JunkoRect);
}
