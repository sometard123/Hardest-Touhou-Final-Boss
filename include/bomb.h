#pragma once
#include <gamelogic.h>
class bomb
{
  public:
    bomb();
    virtual ~bomb();
    void setPosition(double xcoord, double ycoord);
    double getDamageSize();
    double getDamage();
    double getX();
    double getY();
    int getTime();
    void timer();
    virtual void updatePosition()=0; //each bomb has their position updated differently
    virtual void draw(SDL_Renderer *renderer)=0; //bombs might be drawn differently
  protected:
    double x;
    double y;
    int size;
    double damage;
    int time;
  private:
};
