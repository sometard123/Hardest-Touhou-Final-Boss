#include <enemy.h>
#include <SDL2/SDL.h>
#define WINX 480
#define WINY 640
enemy::enemy(double xcoord, double ycoord, double deltax, double deltay)
{
  y = ycoord;
  x = xcoord;
  dx = deltax;
  dy = deltay;
}

void enemy::updatePosition()
{
  x += 2.5 * dx;
  y += 2.5 * dy;
}

double enemy::getX()
{
  return x;
}

double enemy::getY()
{
  return y;
}

void enemy::draw(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 0,255,0,0);
  SDL_Rect enemyRect = {(int)x, (int)y, 10, 10};
  SDL_RenderFillRect(renderer, &enemyRect);
}
