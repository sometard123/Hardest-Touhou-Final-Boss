#pragma once
#include <SDL_stuff.h>
class bullet {
  public:
    //constructor/deconstructor

    bullet();
    virtual ~bullet();
    //setters

    void setDamage(double dmg);
    void setPosition(double x, double y);
    //getters

    double getX();
    double getY();
    double getDamage();
    //misc

    virtual void updatePosition() = 0;
    virtual void draw(SDL_Renderer *renderer);
  protected:
    double xcoord;
    double ycoord;
    double damage;
    double dx;
    double dy;
};
