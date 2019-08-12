#include <star.h>
#include <iostream>

star::star() {
}

star::~star() {
}

//sets position of star
void star::setPosition(int x, int y) {
  this->xcoord = x;
  this->ycoord = y;
}

void star::draw(SDL_Renderer *renderer, SDL_Texture *texture) {
  int w;
  int h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  SDL_Rect rect = {xcoord, ycoord, w - 20, h- 20};
  SDL_RenderCopy(renderer, texture, NULL, &rect);
}

