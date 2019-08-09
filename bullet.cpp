#include <SDL2/SDL.h>
#include <bullet.h>
bullet::bullet()
{
  damage = 2.5;
}
void bullet::setPosition(double x, double y)
{
  this->xcoord = x;
  this->ycoord = y;
}

double bullet::getX()
{
  return xcoord;
}

double bullet::getY()
{
  return ycoord;
}

void bullet::updatePosition()
{
  ycoord -= 25;
}

void bullet::draw(SDL_Renderer *renderer)
{
//  update();
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_Rect bulletRect = {(int)xcoord, (int)ycoord, 10, 10};
  SDL_RenderFillRect(renderer, &bulletRect);
}
