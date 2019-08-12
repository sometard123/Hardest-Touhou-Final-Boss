#include <enemybullet.h>
#include <SDL2/SDL.h>
#define WINX 480
#define WINY 640

//constructor initializes position and direction of enemy bullet
enemybullet::enemybullet(double xcoord, double ycoord, double deltax, double deltay) {
  y = ycoord;
  x = xcoord;
  dx = deltax;
  dy = deltay;
}

enemybullet::~enemybullet() {
}

//updates enemy bullet position with given direction and velocity multiplier of 2.5
void enemybullet::updatePosition() {
  x += 2.5 * dx;
  y += 2.5 * dy;
}

//gets enemy bullet x position
double enemybullet::getX() {
  return x;
}

//gets enemy bullet y position
double enemybullet::getY() {
  return y;
}

//draws enemy bullet
void enemybullet::draw(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0,255,0,0); //sets render draw color to green
  SDL_Rect enemybulletRect = {(int)x, (int)y, 10, 10}; //rectangle at given x and y position with a size of 10x10
  SDL_RenderFillRect(renderer, &enemybulletRect); //renders rectangle
}
