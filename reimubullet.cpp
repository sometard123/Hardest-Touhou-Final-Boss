#include <reimu.h>
#include <bullet.h>
reimu::reimuBullet::reimuBullet() {
}

reimu::reimuBullet::reimuBullet(double deltax, double deltay) {
  dx = deltax;
  dy = deltay;
}

reimu::reimuBullet::~reimuBullet() {
}

void reimu::reimuBullet::updatePosition() {
  ycoord -= dy;
  xcoord += dx;
}

void reimu::reimuBullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //renders bullet color to black
  SDL_Rect bulletRect = {(int)xcoord, (int)ycoord, 10, 10}; //creates a 10 by 10 square at the x and y coordinates specified
  SDL_RenderFillRect(renderer, &bulletRect); //renders the rectangle
}
