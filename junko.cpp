#include <junko.h>
#include <iostream>
using namespace std;

//constructor initiates position and health
junko::junko()
{
  x = 330;
  y = 100;
  health = 2870;
}

junko::~junko()
{
}

//returns junko's xcoordinate
int junko::getX()
{
  return x;
}

//returns junko's y coordinate
int junko::getY()
{
  return y;
}

//updates x position with given velocity
void junko::updateX(double dx)
{
  x += dx;
}

//updates health
int junko::updateHp()
{
  return --health;
}
  
//draws junko
void junko::draw(SDL_Renderer *renderer, SDL_Texture *texture)
{
  int w;
  int h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h); //gets width and height from texture
  //resized width and height to appropriate size
  w /= 4;
  h /= 4;
  SDL_Rect JunkoRect = {x- 49, y - 62, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &JunkoRect);
}
