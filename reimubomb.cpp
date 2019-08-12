#include <reimubomb.h>
#include <reimu.h>
#include <iostream>
using namespace std;
reimu *robj = NULL;
//initializes bomb size and damage in constructor

reimubomb::reimubomb(reimu *r) {
  size = 300;
  damage = 3;
  robj = r;
}

reimubomb::~reimubomb() {
}


void reimubomb::setOnScreen(bool onscrn) {
  onScreen = onscrn;
}

//returns whether bomb is on screen
bool reimubomb::getOnScreen() {
  return onScreen;
}

//updates the position of the bomb
void reimubomb::updatePosition() {
  x = robj->getX() - 118;
  y = robj->getY() - 118;
  robj->update();
}

void reimubomb::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 50, 0, 0, 255);
  SDL_Rect bombRect = {(int)(x), (int)(y), size, size};
  SDL_RenderFillRect(renderer, &bombRect);
}



