#include <gameloop.h>
#include <gamelogic.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;
gamelogic game;
gameloop::gameloop() {
}

gameloop::~gameloop() {
}

//sets frame count
void gameloop::setFrameCount(int frameCnt) {
  frameCount = frameCnt;
}

//gets the last frame passed
int gameloop::getLastFrame() {
  return lastFrame;
}

//gets the frame count
int gameloop::getFrameCount() {
  return frameCount;
}

//game loop
void gameloop::loop() {
  game.initWindow();
  game.setLives(3); //player has 3 lives
  game.initStars();
  game.initHealthBar();
  while (game.getRunning()) {//while game is running
    game.processEvents();
    if (game.getLoading()) {
      if (game.timer() > 100)  {//loading phase only lasts for a brief moment
        game.setLoading(false);
        game.setGame(true);
        game.setTime(0); //timer resets to 0 for later use
      }
    }
    else if (game.getGame()) {
      if (!game.getReimuState())  {//if reimu's dead
        if (game.timer() > 50)  {//pauses for duraction of 50
          game.clearEnemyBullet();
          game.clearBullet();
          game.setTime(0); //timer resets for later use
        }
      }
      else {
        static int i = 0; //ring counter
        if (game.getClear()) {
          if (game.timer() > 10  && i < game.getRings()) {
            game.setJunkoMovement(false); //junko doesn't move when bullets are firing
            game.initEnemyBullet(i);
            game.setTime(0);
            i++;
            if (i == game.getRings()) {
              i = 0;
              game.setJunkoMovement(true); //junko moves when all rings are fired
            }
          }
        } 
        game.update(); //updates position of everything
        //clears bullets if necessary
        game.clearBullet(); 
        game.clearEnemyBullet();
      }
      game.deleteBomb();
    }
    else if (game.getGameOver()) {//gamer loses
      if (game.timer() > 100) {
        game.setRunning(false);
      }
    }
    else {//player wins
      if (game.timer() > 100) {
        game.setRunning(false);
      }
    }
    //frame rate stuff
    /*lastFrame = SDL_GetTicks();
      static int lastTime = 0;
      if (lastFrame >= lastTime + 1000) {
      lastTime = lastFrame;
      frameCount = 0;
      }*/
    SDL_Delay(16);
    game.render();
  }
  game.quit();
}
