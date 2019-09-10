#include <iostream>
#include <cstdlib>
#include <gamelogic.h>
#include <gameloop.h>
#include <stdbool.h>
#include <list>
#include <vector>
#include <bullet.h>
#include <collisionDetection.h>
#include <enemybullet.h>
#include <star.h>
#include <junko.h>
#include <bomb.h>
#include <reimubomb.h>
#include <healthbar.h>
#include <texturemanager.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#define WINX 640
#define WINY 480
#define SIZE 30
using namespace std;

gameloop loop;
reimu reimu;
junko junko;
collisionDetection cd;
enemybullet **enemybulletArray = NULL;
bullet *bobj= NULL;
star starObj;
bomb *bomb = NULL;
//vectors

//vector<star *> starVector;
//vector<healthbar *> healthVector;
//lists

list <enemybullet **> enemybulletList;
list <enemybullet **>::iterator it2;
list <enemybullet **>::iterator it3;

//constructor initializing private variables
gamelogic::gamelogic() {
  time = 0; //indicates that game is beginning
  loading = true; //game starts in the loading stage
  game = false; //play mode is false until game finishes loading
  gameOver = false; //game over initialized to false until player dies
  success = false; //player win screen initialized to false at the start
  clear = true; //screen free of bullets at the start of the game
  counter = 0; //bullets that have passed in the beginning is set to 0
  numRings = 5; //number of rings the junko shoots is initialized to 5
  window = NULL;
  renderer = NULL;
}
gamelogic::~gamelogic() {
}

//sets player's lives
void gamelogic::setLives(int amtLives) {
  this->lives = amtLives;
}

//sets the loading state
void gamelogic::setLoading(bool load) {
  this->loading = load;
}

//sets game mode state
void gamelogic::setGame(bool md) {
  this->game = md;
}

//sets game over statSDL_Renderer *renderere
void gamelogic::setGameOver(bool gmeOver) {
  this->gameOver = gmeOver;
}

//sets win state
void gamelogic::setSuccess(bool win) {
  this->success = win;
}

//sets the time
void gamelogic::setTime(int tm) {
  this->time = tm;
}

//sets the number of rings junko shoots
void gamelogic::setRings(int rings) {
  this->numRings = rings;
}

//sets running state of the program
void gamelogic::setRunning(bool running) {
  isRunning = running;
}

//sets the direction of junko's movement
void gamelogic::setJunkoMovement(bool mvt) {
  movement = mvt;
}

void gamelogic::setClear(bool clr) {
  clear = clr;
}

void gamelogic::setReimuState(bool alive) {
  reimu.setIsAlive(alive);
}

int gamelogic::getTime() {
  return time;
}

//returns the number of rings that junko shoots
int gamelogic::getRings() {
  return numRings;
}

//returns the games running state
bool gamelogic::getRunning() {
  return isRunning;
}

//returns if the screens free of bullets or not
bool gamelogic::getClear() {
  return clear;
}

//returns loading state
bool gamelogic::getLoading() {
  return loading;
}

//returns game mode state
bool gamelogic::getGame() {
  return game;
}

//returns gameover state
bool gamelogic::getGameOver() {
  return gameOver;
}

bool gamelogic::getReimuState() {
  return reimu.getIsAlive();
}

//returns health vector for later use
vector <healthbar*> gamelogic::getHealthBar() {
  return healthVector;
}

vector<star*> gamelogic::getStars() {
  return starVector;
}

//initializes the stars (player lives)
void gamelogic::initStars() {
  starVector.resize(lives); //star vector holds the same amount of stars as lives the player has
  for (unsigned int i = 0; i < starVector.size(); i++) {
    starVector[i] = new star; //allocates memory for a star
    starVector[i]->setPosition(520 + 30 * i, 50); //sets the position of the star so each star is about 30 width apart 
  }
}

//initializes the health bar
void gamelogic::initHealthBar() {
  healthVector.resize(410); //health vector holds 410 elements when boss is at max health
  for (unsigned int i = 0; i < healthVector.size(); i++) {
    healthVector[i] = new healthbar; //allocates memory for a small health chunk
    healthVector[i]->setPosition(20 + i, 40); //sets the position of each health chunk so that they're right next to each other
  }
}

//timer just a counter for now lul
int gamelogic::timer() {
  time++;
  return time;
}

//initiates SDL window
void gamelogic::initWindow() {
  if (!SDL_Init(SDL_INIT_EVERYTHING)) {//inits the SDL library
    TTF_Init(); //inits font library
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0); //creates window at any location with dimensions 640 by 480 called test
    renderer = SDL_CreateRenderer(window, -1, 0); //creates renderer using window
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initializes SDL_Mixer
    dead = Mix_LoadWAV("sounds/se_pldead00.wav"); //loads dying sound 
    fire = Mix_LoadWAV("sounds/se_tan00.wav"); //loads firing sound
    damage = Mix_LoadWAV("sounds/se_lazer02.wav"); //loads damage sound
    bombsound = Mix_LoadWAV("sounds/se_nep00.wav"); 
    reimuTexture = TextureManager::loadTex("Images/Th14ReimuBackSprite.png", renderer); //loads reimu sprite into texture
    playerTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Player", renderer, &font); //loads player font into texture
    loadingTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Loading...", renderer, &font); //loads the loading... font into texture
    gameOverTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Game Over", renderer, &font); //loads game over font into texture
    successTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "You Win!", renderer, &font); //loads you win! font into texture
    starTexture = TextureManager::loadTex("Images/star.png", renderer); //loads star sprite into texture
    junkoTexture = TextureManager::loadTex("Images/Th15Junko.png", renderer); //loads junko sprite into texture
    isRunning = true; //window running is initialized to true
    reimu.setIsAlive(true); //reimu is set to alive
  }
}

void gamelogic::render() {
  if (loading) {//if game is in loading state
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //render color set to black
    SDL_Rect loadingRect = {220, 230, 200, 20}; //rect for "loading..." message is at 220,230 with the dimensions being 200 * 20
    SDL_RenderCopy(renderer, loadingTexture, NULL, &loadingRect); //renders the text to the screen 
  }
  //if game state is true
  else if (game) { 
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); //render draw color set to blue
    SDL_RenderClear(renderer); //clears the render color to the screen
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); //render draw color set to green
    SDL_Rect rightSide = {450, 0, 190, 480}; //rectangle for the right side of the screen
    SDL_RenderFillRect(renderer, &rightSide); //renders the right side of the screen
    SDL_Rect textRect = {480, 50, 40, 30}; //text rect for "player"
    SDL_RenderCopy(renderer, playerTexture, NULL, &textRect); //renders "player" to screen
    //draws bomb if existent
    /*if (bomb) {
      bomb->draw(renderer);
      }*/
    //draws reimu only if alive
    if (reimu.getIsAlive()) {
      reimu.draw(renderer, reimuTexture);
    }
    junko.draw(renderer, junkoTexture); //draws junko
    //draws stars
    for (unsigned int i = 0; i < starVector.size(); i++) {
      starVector[i]->draw(renderer, starTexture);
    }
    //draws bullets
    /*for (int i = 0; i < 4; i++) {
      for (it = bulletList[i].begin(); it != bulletList[i].end(); it++) {
      if (*it) {
      (*it)->draw(renderer);
      }
      }
      }*/
    //draws enemy bullets
    /*for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++) {
      if (*it2) {
      for (int i = 0; i < SIZE; i++) {
      if ((*it2)[i]) {
      (*it2)[i]->draw(renderer);
      }
      }
      }
      }*/
    //draws health bar
    for (unsigned int i = 0; i < healthVector.size(); i++) {
      healthVector[i]->draw(renderer);
    }
  }
  //if the game is over
  else if (gameOver) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //render color set to black
    SDL_RenderClear(renderer); //clears render color to screen
    SDL_Rect rect = {220, 230, 200, 20}; //text rect for "game over"
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &rect); //renders the "game over" message
  }
  //if player wins
  else {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //render color set to black
    SDL_RenderClear(renderer); //clears render color to screen
    SDL_Rect rect = {240, 230, 160, 20}; //rect for "you win"
    SDL_RenderCopy(renderer, successTexture, NULL, &rect); //renders "you win" rect
  }
  /*
  //displays stuff at 60 fps
  int frameCount = loop.getFrameCount();
  loop.setFrameCount(++frameCount);
  int timerFPS = SDL_GetTicks() - loop.getLastFrame();
  SDL_Delay(1000/60 - timerFPS);
  */
  SDL_RenderPresent(renderer); //presents renderer
}

//processes keyboard and cursor events
void gamelogic::processEvents() {
  SDL_Event event;
  //polls events
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_WINDOWEVENT_CLOSE: //if someone clicks x 
        if (window) {
          SDL_DestroyWindow(window); //destroys window
          window = NULL; //window points to null
          isRunning = false; //sdl window no longer running
        }
        break;
      case SDL_KEYDOWN: //if a key is pressed
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE: //when esc is pressed
            isRunning = false; //sdl window no longer running
            break;
          case SDLK_x:
            reimu.initBomb();
            Mix_PlayChannel(2,bombsound, 0);
        }
        break;
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
    }
  }
}

//collision detection with rectangular hitboxes
int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2) {
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

//collision detection with circuluar hitboxes
int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2) {
  return !(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) > r1 + r2);
} 

void gamelogic::handleCollisions(gamelogic
    & gobj) {
  if (reimu.getIsAlive()) {
    cd.reimuBulletsWithJunko(reimu, junko, gobj);
    cd.reimuWithJunkoBullets(reimu, junko, gobj, dead);
    cd.reimuBombWithJunkoBullets(reimu, junko, gobj);
    cd.reimuBombWithJunko(reimu, junko, gobj);
  }
}

void gamelogic::handleBullets() {
  reimu.initBullets(damage);
  reimu.clearBullet();
}

void gamelogic::handleBomb() {
  if (reimu.getBomb()) {
    reimu.getBomb()->updatePosition();
  }
  reimu.destroyBomb();
}

//inititiates the enemy bullets
void gamelogic::initEnemyBullet(int i, gamelogic &gobj) {
  junko.initBullets(gobj, i, fire);
}

void gamelogic::updateStars() {
  starVector.pop_back();
}

//updates position of all objects 
void gamelogic::update() {
  static double dx = 1; //x component of velocity is 1
  if (reimu.getIsAlive()) {
    //updates reimu's position
    reimu.update();
    //updates bomb position
    if (bomb) {
      bomb->updatePosition();
    }
    //updates junko's position
    if (movement) {//if junko is moving
      if (junko.getX() > 450) {//if junko reaches right edge direction is reversed
        dx = -dx;
      }
      else if (junko.getX() < 0) {//if junko reaches left edge direction is reversed
        dx = -dx;
      }
      junko.updateX(dx); //calls junko's update direction function
    }
    junko.updateBullets();
  }
}

//updates the health bar if junko is shot
void gamelogic::updateHealthBar() {
  if (junko.updateHp() % 7 == 0) {//took mod of 7 because health is 7 * 410, 410 being the initial size of the vector
    //removes a small health segment if multiples of 7 health are removed
    delete healthVector.back();
    healthVector.pop_back();
  }
}

//clears enemy bullet
void gamelogic::clearEnemyBullet(gamelogic &gobj) {
  junko.clearBullets(gobj);
}

//things to do when game quits
void gamelogic::quit() {
  //clears health bar
  for (unsigned int i = 0; i < healthVector.size(); i++) {
    delete healthVector[i];
  }
  SDL_DestroyTexture(reimuTexture);
  SDL_DestroyTexture(playerTexture);
  SDL_DestroyTexture(starTexture);
  SDL_DestroyTexture(junkoTexture);
  SDL_DestroyTexture(loadingTexture);
  SDL_DestroyTexture(gameOverTexture);
  SDL_DestroyTexture(successTexture);
  //destroys fonts
  TTF_CloseFont(font);
  TTF_Quit();
  //destroy window and renderer
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  //frees sound chunks
  Mix_FreeChunk(dead);
  Mix_FreeChunk(fire);
  Mix_FreeChunk(damage);
  Mix_FreeChunk(bombsound);
  IMG_Quit(); //quits image library
  SDL_Quit();
  //destroys textures
}
