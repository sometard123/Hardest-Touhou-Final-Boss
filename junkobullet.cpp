#include <junko.h>
#include <enemyBullet.h>
junko::junkoBullet::junkoBullet(double x, double y, double deltax, double deltay) {
  ycoord = y;
  xcoord = x;
  dx = deltax;
  dy = deltay;
  size = 10;
}

junko::junkoBullet::~junkoBullet() {
}

void junko::junkoBullet::updatePosition() {
  xcoord += 2.5 * dx;
  ycoord += 2 * dy;
//  size += 0.3;
}

void junko::junkoBullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0,150, 0, 0); //sets render draw color to green
  SDL_Rect rect = {(int)xcoord, (int)ycoord, (int)size, (int)size}; //rectangle at given x and y position with a size of 10x10
  SDL_RenderFillRect(renderer, &rect); //renders rectangle
}

