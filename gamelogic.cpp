#include <iostream>
#include <cstdlib>
#include <gamelogic.h>
#include <gameloop.h>
#include <stdbool.h>
#include <list>
#include <vector>
#include <bullet.h>
#include <enemy.h>
#include <star.h>
#include <junko.h>
#include <healthbar.h>
#include <texturemanager.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#define WINX 450
#define WINY 480
#define SIZE 75
using namespace std;

gameloop loop;
reimu reimu;
junko junko;
list <bullet*> bulletList[4];
list<bullet *>::iterator it;
list <enemy **> enemyList;
list <enemy **>::iterator it2;
list <enemy **>::iterator it3;
enemy **enemyArray = NULL;
bullet *bobj= NULL;
star starObj;
vector<star *> starVector;
vector<healthbar *> healthVector;
gamelogic::gamelogic()
{
  time = 0;
  loading = true;
  game = false;
  gameOver = false;
  success = false;
  clear = true;
  counter = 0;
  counter2 = 0;
  numRings = 5;
}
gamelogic::~gamelogic()
{
}

void gamelogic::setLives(int amtLives)
{
  this->lives = amtLives;
}

void gamelogic::setLoading(bool load)
{
  this->loading = load;
}

void gamelogic::setGame(bool md)
{
  this->game = md;
}

void gamelogic::setGameOver(bool gmeOver)
{
  this->gameOver = gmeOver;
}

void gamelogic::setSuccess(bool win)
{
  this->success = win;
}

void gamelogic::setTime(int tm)
{
  this->time = tm;
}

void gamelogic::setRings(int rings)
{
  this->numRings = rings;
}

void gamelogic::setRunning(bool running)
{
  isRunning = running;
}

void gamelogic::setJunkoMovement(bool mvt)
{
  movement = mvt;
}

int gamelogic::getRings()
{
  return numRings;
}

bool gamelogic::getRunning()
{
  return isRunning;
}

bool gamelogic::getClear()
{
  return clear;
}

bool gamelogic::getLoading()
{
  return loading;
}

bool gamelogic::getGame()
{
  return game;
}

bool gamelogic::getGameOver()
{
  return gameOver;
}

void gamelogic::initStars()
{
  starVector.resize(lives);
  for (unsigned int i = 0; i < starVector.size(); i++)
  {
    starVector[i] = new star;
    starVector[i]->setPosition(520 + 30 * i, 50);  
  }
}

void gamelogic::initHealthBar()
{
  healthVector.resize(410);
  for (unsigned int i = 0; i < healthVector.size(); i++)
  {
    healthVector[i] = new healthbar;
    healthVector[i]->setPosition(20 + i, 40);
  }
}

int gamelogic::timer()
{
  time++;
  return time;
}

void gamelogic::initWindow(Mix_Chunk **effect)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    TTF_Init();
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, WINY, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    *effect = Mix_LoadWAV("sounds/se_pldead00.wav");
    fire = Mix_LoadWAV("sounds/se_tan00.wav");
    damage = Mix_LoadWAV("sounds/se_lazer02.wav");
    reimuTexture = TextureManager::loadTex("Images/Th14ReimuBackSprite.png", renderer);
    playerTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Player", renderer, &font);
    loadingTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Loading...", renderer, &font);
    gameOverTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "Game Over", renderer, &font);
    successTexture = TextureManager::loadTex("fonts/AldotheApache.ttf", "You Win!", renderer, &font);
    starTexture = TextureManager::loadTex("Images/star.png", renderer);
    junkoTexture = TextureManager::loadTex("Images/Th15Junko.png", renderer);
    isRunning = true;
    reimu.setIsAlive(true);
  }
}

void gamelogic::render() 
{
  if (loading)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect loadingRect = {220, 230, 200, 20};
    SDL_RenderCopy(renderer, loadingTexture, NULL, &loadingRect); 
  }
  else if (game)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
    SDL_Rect rightSide = {450, 0, 190, 480};
    SDL_RenderFillRect(renderer, &rightSide);
    SDL_Rect textRect = {480, 50, 40, 30};
    SDL_RenderCopy(renderer, playerTexture, NULL, &textRect);
    if (reimu.getIsAlive())
    {
      reimu.draw(renderer, reimuTexture);
    }
    junko.draw(renderer, junkoTexture);
    for (unsigned int i = 0; i < starVector.size(); i++)
    {
      starVector[i]->draw(renderer, starTexture);
    }
    for (int i = 0; i < 4; i++)
    {
      for (it = bulletList[i].begin(); it != bulletList[i].end(); it++)
      {
        if (*it)
        {
          (*it)->draw(renderer);
        }
      }
    }
    for (it2 = enemyList.begin(); it2 != enemyList.end(); it2++)
    {
      if (*it2)
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j] != NULL)
          {
            (*it2)[j]->draw(renderer);
          }
        }
      }
    }
    for (unsigned int i = 0; i < healthVector.size(); i++)
    {
      healthVector[i]->draw(renderer);
    }
  }
  else if (gameOver)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rect = {220, 230, 200, 20};
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &rect);
  }
  else
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rect = {240, 230, 160, 20};
    SDL_RenderCopy(renderer, successTexture, NULL, &rect);
  }
  int frameCount = loop.getFrameCount();
  loop.setFrameCount(frameCount++);
  int timerFPS = SDL_GetTicks() - loop.getLastFrame();
  if (timerFPS < 1000/60)
  {
    SDL_Delay(1000/60 - timerFPS);
  }
  SDL_RenderPresent(renderer);
}

void gamelogic::processEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_WINDOWEVENT_CLOSE: 
        if (window)
        {
          SDL_DestroyWindow(window);
          window = NULL;
          isRunning = false;
        }
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE:
            isRunning = false;
        }
        break;
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
    }
  }
  state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_Z] && reimu.getIsAlive() && game && true)
  {
    Mix_Volume(0, 50); 
    Mix_PlayChannel(0, damage, 0);
    for (int i = 0; i < 4; i++)
    {
      bobj= new bullet;
      bulletList[i].push_back(bobj);
      switch (i)
      {
        case 0:
          bulletList[i].back()->setPosition(reimu.getX(), reimu.getY());
          break;
        case 1:
          bulletList[i].back()->setPosition(reimu.getX() + i * 20, reimu.getY());
          break;
        case 2:
          bulletList[i].back()->setPosition(reimu.getX() + i * 20, reimu.getY());
          break;
        case 3:
          bulletList[i].back()->setPosition(reimu.getX() + i * 20, reimu.getY());
          break;
        default: break;
      }
    }
  }
}

int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2)
{
  return !(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) > r1 + r2);
} 

void gamelogic::genEnemy(int i)
{
  double dx;
  double dy;
  enemyList.resize(numRings);
  it2 = enemyList.begin();
  it3 = it2;
  advance(it2,i);
  advance(it3, numRings - 1);
  Mix_PlayChannel(-1, fire, 0);
  random = (rand() % 360) * M_PI/180;
  if (it2 == it3)
  {
    clear = false;
  }
  enemyArray = new enemy*[SIZE];
  for (int index = 0; index < SIZE; index++)
  {
    dx = cos((index * 2 * M_PI + random) / (SIZE));
    dy = sin((index * 2 * M_PI + random) / (SIZE));
    enemyArray[index] = new enemy(junko.getX(), junko.getY(), dx, dy);
  }
  enemyList.insert(it2, enemyArray);
}

void gamelogic::clearBullet()
{
  if (reimu.getIsAlive())
  {
    for (int i = 0; i < 4; i++)
    {
      if (bulletList[i].size())
      {
        if (bulletList[i].front())
        {
          if (bulletList[i].front()->getY() <= 0)
          {
            delete bulletList[i].front();
            bulletList[i].pop_front();
          }
        }
      }
    }
    for (int i = 0; i < 4; i++)
    {
      for (it = bulletList[i].begin(); it != bulletList[i].end(); it++)
      {
        if (*it)
        {
          if (collisionDetection(junko.getX(), junko.getY(), (*it)->getX(), (*it)->getY(), 49, 5))
          {
            if (healthVector.size())
            {
              updateHealthBar();
            }
            else
            {
              game = false;
              success = true;
            }
            delete (*it);
            (*it) = NULL;
            //bulletList[i].erase(it);
          }
        }
      }
    }
  }
  else
  {
    for (int i = 0; i < 4; i++)
    {
      if (bulletList[i].size())
      {
        bulletList[i].erase(bulletList[i].begin(), bulletList[i].end());
      }
    }
  }
}

void gamelogic::updateEnemy()
{
  static double dx = 1;
  if (reimu.getIsAlive())
  {

    //updates reimu's position
    reimu.update();

    if (movement)
    {
      if (junko.getX() > 450)
      {
        dx = -dx;
      }
      else if (junko.getX() < 0)
      {
        dx = -dx;
      }
      junko.updateX(dx);
    }

    //updates bullets position
    for (int i = 0; i < 4; i++)
    {
      for (it = bulletList[i].begin(); it!= bulletList[i].end(); it++)
      {
        if (*it)
        {
          (*it)->updatePosition();
        }
      }
    }    

    //updates enemy bullets position
    for (it2 = enemyList.begin(); it2 != enemyList.end(); it2++)
    {
      if (*it2)
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j] != NULL)
          {
            (*it2)[j]->updatePosition();
          }
        }
      }
    }
  }
}

void gamelogic::updateHealthBar()
{
  if (junko.updateHp() % 7 == 0)
  {
    delete healthVector.back();
    healthVector.pop_back();
  }
}
void gamelogic::clearEnemy(Mix_Chunk **effect)
{
  if (reimu.getIsAlive())
  {
    for (it2 = enemyList.begin(); it2 != enemyList.end(); it2++)
    {
      if (*it2)
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j] != NULL)
          {
            if ((*it2)[j]->getX() < 0)
            {
              counter++;
              delete (*it2)[j];
              (*it2)[j] = NULL;
            } 
            else if ((*it2)[j]->getX() > 450)
            {
              counter++;
              delete (*it2)[j];
              (*it2)[j] = NULL;
            }
            else if ((*it2)[j]->getY() < 0)
            {
              counter++;
              delete (*it2)[j];
              (*it2)[j] = NULL;
            }
            else if ((*it2)[j]->getY() > WINY)
            {
              counter++;
              delete (*it2)[j];
              (*it2)[j] = NULL;
            }
            else if (collisionDetection(reimu.getHitboxX(), reimu.getHitboxY(), (*it2)[j]->getX(), (*it2)[j]->getY(),3, 5))
            {
              counter = 0;
              Mix_PlayChannel(0, *effect, 0);
              delete (*it2)[j];
              (*it2)[j] = NULL;
              reimu.setIsAlive(false); 
              if (starVector.size())
              {
                starVector.pop_back();
              }
              else
              {
                game = false;
                gameOver = true;
              }
            }
          }
        }
      }
    }
    if (counter == numRings * SIZE)
    {
      for (it2 = enemyList.begin(); it2 != enemyList.end(); it2++)
      {
        if (*it2)
        {
          delete[] *it2;
          (*it2) = NULL;
        }
      }
      enemyList.clear();
      counter = 0;
      clear = true;
      setRings(++numRings);
    }
  }
  else
  {
    for (it2 = enemyList.begin(); it2 != enemyList.end(); it2++)
    {
      if (*it2)
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j] != NULL)
          {
            delete (*it2)[j];
            (*it2)[j] = NULL;
          }
        }
        delete[] (*it2);
        *it2 = NULL;
      }
    }
    enemyList.clear();
    clear = true;
    reimu.setIsAlive(true);
  }
}

bool gamelogic::getReimuState()
{
  return reimu.getIsAlive();
}

void gamelogic::quit(Mix_Chunk **effect)
{
  for (int i = 0; i < 4; i++)
  {
    bulletList[i].clear();
  }

  for (unsigned int i = 0; i < healthVector.size(); i++)
  {
    delete healthVector[i];
  }
  IMG_Quit();
  SDL_Quit();
  SDL_DestroyTexture(reimuTexture);
  SDL_DestroyTexture(playerTexture);
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  Mix_FreeChunk(*effect);
  Mix_FreeChunk(fire);
  Mix_FreeChunk(damage);
}
