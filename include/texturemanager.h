#pragma once
#include <gameloop.h>
#include <SDL2/SDL_ttf.h>
class TextureManager
{
  public:
    //load textures
    static SDL_Texture *loadTex(const char* fileName, SDL_Renderer *renderer);
    static SDL_Texture *loadTex(const char* file, const char* text, SDL_Renderer *renderer, TTF_Font **font);
  private:
};
