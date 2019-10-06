#include <texturemanager.h>
#include <iostream>
#include <cstdlib>
using namespace std;
SDL_Texture *TextureManager::loadTex(const char* file, SDL_Renderer *renderer) {
  SDL_Surface *tmp = IMG_Load(file); //loads image into surface
  if (tmp == NULL) {
    cout << file << "was not found!" << endl;
    exit(EXIT_FAILURE);
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);
  return texture;
}

SDL_Texture *TextureManager::loadTex(const char* file, const char* text, SDL_Renderer *renderer, TTF_Font **font)
{
  SDL_Color color = {255, 255, 255, 255};
  *font = TTF_OpenFont(file, 16); //opens font file and loads it into the font variable
  if (font == NULL) {
    cout << file << " was not found!" << endl;
    exit(EXIT_FAILURE);
  }
  SDL_Surface *tmp = TTF_RenderText_Blended(*font, text, color);  //creates a surface from font
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tmp); 
  SDL_FreeSurface(tmp);
  TTF_CloseFont(*font);
  return texture;
}


