#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
class gameloop
{
  public:
    gameloop();
    ~gameloop();
    void setFrameCount(int frameCnt);
    int getLastFrame();
    int getFrameCount();
    void loop();
  private:
    Mix_Chunk *effect; 
    int frameCount;
    int lastFrame;
};
