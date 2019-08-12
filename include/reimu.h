#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
class reimu {
  public:
    //constructor/deconstructor

    reimu();
    ~reimu();
    //setters

    void setIsAlive(bool alive);
    //getters

    bool getIsAlive();
    double getX();
    double getY();
    double getHitboxX();
    double getHitboxY();
    //misc

    void update();
    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
    void collisionDetection();
  private:
    typedef struct
    {
      double x;
      double y;
    }Hitbox;
    Hitbox h;
    const Uint8* state;
    double x;
    double y;
    double velocity;
    double diagonalVelocity;
    bool isAlive;
};
