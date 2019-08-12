#pragma once
#include <SDL2/SDL.h>
class enemybullet {
  public:
    //constructor/deconstructor

    enemybullet(double xcoord, double ycoord, double deltax, double deltay);
    ~enemybullet();
    //getters

    double getX();
    double getY();
    //misc

    void updatePosition();
    void draw(SDL_Renderer *renderer);
  private:
    double x;
    double y;
    double dx;
    double dy;
};
