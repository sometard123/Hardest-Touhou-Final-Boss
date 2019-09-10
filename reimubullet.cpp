#include <reimu.h>
#include <bullet.h>

reimu::reimuBullet::~reimuBullet() {
}

void reimu::reimuBullet::updatePosition() {
  ycoord -= 25;
}

void reimu::reimuBullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //renders bullet color to black
  SDL_Rect bulletRect = {(int)xcoord, (int)ycoord, 10, 10}; //creates a 10 by 10 square at the x and y coordinates specified
  SDL_RenderFillRect(renderer, &bulletRect); //renders the rectangle
}
