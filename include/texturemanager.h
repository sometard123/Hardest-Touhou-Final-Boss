#pragma once
#include <non1loop.h>
#include <SDL_stuff.h>
class TextureManager {
  public:
    //load textures
    static SDL_Texture *loadTex(const char* fileName, SDL_Renderer *renderer);
    static SDL_Texture *loadTex(const char* file, const char* text, SDL_Renderer *renderer, TTF_Font **font);
  private:
};
