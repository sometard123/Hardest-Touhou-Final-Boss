#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
class gameloop {
  public:
    //constructor/deconstructor

    gameloop();
    ~gameloop();
    //setters

    void setFrameCount(int frameCnt);
    //getters

    int getLastFrame();
    int getFrameCount();
    //misc

    void loop();
  private:
    int frameCount;
    int lastFrame;
};
