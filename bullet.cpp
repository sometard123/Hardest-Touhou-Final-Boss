#include <SDL2/SDL.h>
#include <bullet.h>

//constructor initializes bullet damage
bullet::bullet() {
  damage = 2.5;
}

bullet::~bullet() {
}

//sets the x and y coordinates of the bullet
void bullet::setPosition(double x, double y) {
  this->xcoord = x;
  this->ycoord = y;
}

//returns the x coordinate of the bullet
double bullet::getX() {
  return xcoord;
}

//returns the y coordinate of the bullet
double bullet::getY() {
  return ycoord;
}

//makes bullet move up the screen with a velocity of 25
void bullet::updatePosition() {
  ycoord -= 25;
}

//draws bullet
void bullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //renders bullet color to black
  SDL_Rect bulletRect = {(int)xcoord, (int)ycoord, 10, 10}; //creates a 10 by 10 square at the x and y coordinates specified
  SDL_RenderFillRect(renderer, &bulletRect); //renders the rectangle
}
