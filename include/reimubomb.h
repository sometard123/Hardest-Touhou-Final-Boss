#pragma once
#include <bomb.h>
#include <SDL_stuff.h>
class reimubomb: public bomb {
  public:
    reimubomb(reimu *);
    virtual ~reimubomb();
    void setOnScreen(bool onscrn);
    bool getOnScreen();
    virtual void updatePosition();
    virtual void draw(SDL_Renderer *renderer);
  private:
    bool onScreen;
};

