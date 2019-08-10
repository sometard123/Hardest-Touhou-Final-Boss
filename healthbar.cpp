#include <healthbar.h>
#include <iostream>

using namespace std;

healthbar::healthbar()
{
}

healthbar::~healthbar()
{
}

//sets x and y coordinates of healthbar
void healthbar::setPosition(double x, double y)
{
  this->xcoord = x;
  this->ycoord = y;
}
//draws healthbar
void healthbar::draw(SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0); //sets the color of the healthbar
  SDL_Rect healthBarRect = {(int)xcoord, (int)ycoord, 1, 20}; //makes a 1x20 rectangle at the desired location
  SDL_RenderFillRect(renderer, &healthBarRect); //draws the rectangle
}
