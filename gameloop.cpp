#include <gameloop.h>
#include <gamelogic.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;
gamelogic game;
gameloop::gameloop()
{
}

gameloop::~gameloop()
{
}

void gameloop::setFrameCount(int frameCnt)
{
  frameCount = frameCnt;
}

int gameloop::getLastFrame()
{
  return lastFrame;
}

int gameloop::getFrameCount()
{
 return frameCount;
}

void gameloop::loop()
{
  game.initWindow(&effect);
  game.setLives(3);
  game.initStars();
  game.initHealthBar();
  while (game.getRunning()) 
  {
    game.processEvents();
    if (game.getLoading())
    {
      if (game.timer() > 100)
      {
        game.setLoading(false);
        game.setGame(true);
        game.setTime(0);
      }
    }
    else if (game.getGame())
    {
      if (!game.getReimuState())
      {
        if (game.timer() > 50)
        {
          game.clearEnemy(&effect);
          game.clearBullet();
          game.setTime(0);
        }
      }
      else
      {
        static int i = 0;
        if (game.getClear())
        {
          if (game.timer() > 10  && i < game.getRings())
          {
            game.setJunkoMovement(false);
            game.genEnemy(i);
            game.setTime(0);
            i++;
            if (i == game.getRings())
            {
              i = 0;
              game.setJunkoMovement(true);
            }
          }
        } 
        game.updateEnemy();
        game.clearBullet();
        game.clearEnemy(&effect);
      }
    }
    else if (game.getGameOver())
    {
      if (game.timer() > 100)
      {
        game.setRunning(false);
      }
    }
    else
    {
      if (game.timer() > 100)
      {
        game.setRunning(false);
      }
    }
    lastFrame = SDL_GetTicks();
    static int lastTime = 0;
    if (lastFrame >= lastTime + 1000)
    {
      lastTime = lastFrame;
      frameCount = 0;
    }
    game.render();
    SDL_Delay(16);
  }
  game.quit(&effect);
}


