#pragma once
#include <bullet.h>
#include <SDL_stuff.h>
class enemybullet: public bullet {
  public:
    //constructor/deconstructor
    enemybullet();
    enemybullet(double x, double y, double deltax, double deltay);
    virtual ~enemybullet();
    virtual void updatePosition();
    //getters

    double getSize();
    //misc
    virtual void draw(SDL_Renderer *renderer);
  protected:
    double size;
    double dx; 
    double dy;
};
