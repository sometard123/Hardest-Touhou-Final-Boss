#pragma once
#include <gamelogic.h>
#include <enemybullet.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <list>
class junko {
  public:
    //constructor/deconstructor

    junko();
    ~junko();
    //setters and getters

    void setCounter(int cnt);
    int getCounter();
    int getX();
    int getY();
    //init

    void initBullets(gamelogic &gobj, int i, Mix_Chunk *fire);
    void clearBullets(gamelogic &gobj);
    //other member functions

    void updateX(double dx);
    int updateHp();
    void updateBullets();
    void draw(SDL_Renderer *renderer, SDL_Texture *texture);
    int timer();
    friend class collisionDetection;
    class junkoBullet: public enemybullet {
      public: 
        junkoBullet(double x, double y, double deltax, double deltay);
        virtual ~junkoBullet();
        virtual void updatePosition();
        virtual void draw(SDL_Renderer *renderer);
    };
  private:
    int x;
    int y;
    int health;
    int numRings;
    int counter;
    list <junkoBullet **> bulletList;
    list <junkoBullet **>::iterator it;
    list <junkoBullet **>::iterator it2;
    junkoBullet ** bulletArray;
    int time;
};
