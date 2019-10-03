#include <non1loop.h>
#include <non1logic.h>
#include <iostream>
using namespace std;
non1loop::non1loop() {
}
non1loop::non1loop(reimu ro) {
  object = ro;
}

non1loop::~non1loop() {
}

//sets frame count
//game loop
void non1loop::loop() {
  gamelogic game;
  game.initWindow();
  game.setLives(3); //player has 3 lives
  //  game.initStars();
  //  game.initBombStars();
  game.initHealthBar();
  while (game.getRunning()) {
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
        game.clearEnemyBullet(game);
        game.setTime(0); //timer resets for later use
      }
      else {
        static int i = 0; //ring counter
        if (game.getClear()) {
          if (game.timer() > 9  && i < game.getRings()) {
            game.setJunkoMovement(false); //junko doesn't move when bullets are firing
            game.initEnemyBullet(i, game);
            game.setTime(0);
            i++;
            if (i == game.getRings()) {
              i = 0;
              game.setJunkoMovement(true); //junko moves when all rings are fired
              game.setClear(false);
            }
          }
        } 
        game.handleCollisions(game);
        game.handleBullets();
        game.handleBomb();
        game.update(); //updates position of everything
        //clears bullets if necessary
        game.clearEnemyBullet(game);
      }
      //      game.deleteBomb();
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
