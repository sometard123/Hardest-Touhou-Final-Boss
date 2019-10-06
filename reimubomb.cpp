#include <reimu.h>
#include <iostream>
using namespace std;
//initializes bomb size and damage in constructor

reimu::reimuBomb::reimuBomb(reimu *robj) {
  current = robj;
  size = 300;
  damage = 10;
}

reimu::reimuBomb::~reimuBomb() {
}

//updates the position of the bomb
void reimu::reimuBomb::updatePosition() {
  bombx = current->x - 118;
  bomby = current->y - 118;
}

void reimu::reimuBomb::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
  SDL_Rect bombRect = {(int)(bombx), (int)(bomby), size, size};
  SDL_RenderFillRect(renderer, &bombRect);
}
