#include <enemybullet.h>
#include <SDL2/SDL.h>
#define WINX 480
#define WINY 640

enemybullet::enemybullet() {
}

//constructor initializes position and direction of enemy bullet
enemybullet::enemybullet(double x, double y, double deltax, double deltay) {
  ycoord = y;
  xcoord = x;
  dx = deltax;
  dy = deltay;
  size = 10;
}

enemybullet::~enemybullet() {
}

//updates enemy bullet position with given direction and velocity multiplier of 2.5
void enemybullet::updatePosition() {
  xcoord += 2.5 * dx;
  ycoord += 2 * dy;
//  size += 0.3;
}

double enemybullet::getSize() {
  return size;
}
//draws enemy bullet
void enemybullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0,150, 0, 0); //sets render draw color to green
  SDL_Rect enemybulletRect = {(int)xcoord, (int)ycoord, (int)size, (int)size}; //rectangle at given x and y position with a size of 10x10
  SDL_RenderFillRect(renderer, &enemybulletRect); //renders rectangle
}
