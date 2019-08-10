#include <iostream>
#include <cstdlib>
#include <gamelogic.h>
#include <gameloop.h>
#include <stdbool.h>
#include <list>
#include <vector>
#include <bullet.h>
#include <enemybullet.h>
#include <star.h>
#include <junko.h>
#include <healthbar.h>
#include <texturemanager.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <cmath>
#define WINX 640
#define WINY 480
#define SIZE 75
using namespace std;

gameloop loop;
reimu reimu;
junko junko;
enemybullet **enemybulletArray = NULL;
bullet *bobj= NULL;
star starObj;
//vectors

vector<star *> starVector;
vector<healthbar *> healthVector;
//lists

list <bullet*> bulletList[4];
list<bullet *>::iterator it;
list <enemybullet **> enemybulletList;
list <enemybullet **>::iterator it2;
list <enemybullet **>::iterator it3;

//constructor initializing private variables
gamelogic::gamelogic()
{
  time = 0; //indicates that game is beginning
  loading = true; //game starts in the loading stage
  game = false; //play mode is false until game finishes loading
  gameOver = false; //game over initialized to false until player dies
  success = false; //player win screen initialized to false at the start
  clear = true; //screen free of bullets at the start of the game
  counter = 0; //bullets that have passed in the beginning is set to 0
  numRings = 5; //number of rings the junko shoots is initialized to 5
}
gamelogic::~gamelogic()
{
}

//sets player's lives
void gamelogic::setLives(int amtLives)
{
  this->lives = amtLives;
}

//sets the loading state
void gamelogic::setLoading(bool load)
{
  this->loading = load;
}

//sets game mode state
void gamelogic::setGame(bool md)
{
  this->game = md;
}

//sets game over state
void gamelogic::setGameOver(bool gmeOver)
{
  this->gameOver = gmeOver;
}

//sets win state
void gamelogic::setSuccess(bool win)
{
  this->success = win;
}

//sets the time
void gamelogic::setTime(int tm)
{
  this->time = tm;
}

//sets the number of rings junko shoots
void gamelogic::setRings(int rings)
{
  this->numRings = rings;
}

//sets running state of the program
void gamelogic::setRunning(bool running)
{
  isRunning = running;
}

//sets the direction of junko's movement
void gamelogic::setJunkoMovement(bool mvt)
{
  movement = mvt;
}

//returns the number of rings that junko shoots
int gamelogic::getRings()
{
  return numRings;
}

//returns the games running state
bool gamelogic::getRunning()
{
  return isRunning;
}

//returns if the screens free of bullets or not
bool gamelogic::getClear()
{
  return clear;
}

//returns loading state
bool gamelogic::getLoading()
{
  return loading;
}

//returns game mode state
bool gamelogic::getGame()
{
  return game;
}

//returns gameover state
bool gamelogic::getGameOver()
{
  return gameOver;
}

//initializes the stars (player lives)
void gamelogic::initStars()
{
  starVector.resize(lives); //star vector holds the same amount of stars as lives the player has
  for (unsigned int i = 0; i < starVector.size(); i++)
  {
    starVector[i] = new star; //allocates memory for a star
    starVector[i]->setPosition(520 + 30 * i, 50); //sets the position of the star so each star is about 30 width apart 
  }
}

//initializes the health bar
void gamelogic::initHealthBar()
{
  healthVector.resize(410); //health vector holds 410 elements when boss is at max health
  for (unsigned int i = 0; i < healthVector.size(); i++)
  {
    healthVector[i] = new healthbar; //allocates memory for a small health chunk
    healthVector[i]->setPosition(20 + i, 40); //sets the position of each health chunk so that they're right next to each other
  }
}

//timer just a counter for now lul
int gamelogic::timer()
{
  time++;
  return time;
}

//initiates SDL window
void gamelogic::initWindow()
{
  if (!SDL_Init(SDL_INIT_EVERYTHING)) //inits the SDL library
  {
    TTF_Init(); //inits font library
    window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINX, WINY, 0); //creates window at any location with dimensions 640 by 480 called test
    renderer = SDL_CreateRenderer(window, -1, 0); //creates renderer using window
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initializes SDL_Mixer
    dead = Mix_LoadWAV("sounds/se_pldead00.wav"); //loads dying sound 
    fire = Mix_LoadWAV("sounds/se_tan00.wav"); //loads firing sound
    damage = Mix_LoadWAV("sounds/se_lazer02.wav"); //loads damage sound
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

void gamelogic::render() 
{
  if (loading) //if game is in loading state
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //render color set to black
    SDL_Rect loadingRect = {220, 230, 200, 20}; //rect for "loading..." message is at 220,230 with the dimensions being 200 * 20
    SDL_RenderCopy(renderer, loadingTexture, NULL, &loadingRect); //renders the text to the screen 
  }
  else if (game) //if game state if true
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); //render draw color set to blue
    SDL_RenderClear(renderer); //clears the render color to the screen
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0); //render draw color set to green
    SDL_Rect rightSide = {450, 0, 190, 480}; //rectangle for the right side of the screen
    SDL_RenderFillRect(renderer, &rightSide); //renders the right side of the screen
    SDL_Rect textRect = {480, 50, 40, 30}; //text rect for "player"
    SDL_RenderCopy(renderer, playerTexture, NULL, &textRect); //renders "player" to screen
    if (reimu.getIsAlive()) //draws reimu only if she's alive
    {
      reimu.draw(renderer, reimuTexture);
    }
    junko.draw(renderer, junkoTexture); //draws junko
    for (unsigned int i = 0; i < starVector.size(); i++) //draws all the stars
    {
      starVector[i]->draw(renderer, starTexture);
    }

    //draws bullets
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

    //draws enemy bullets
    for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++)
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

    //draws health bar
    for (unsigned int i = 0; i < healthVector.size(); i++)
    {
      healthVector[i]->draw(renderer);
    }
  }
  else if (gameOver) //if the game is over
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //render color set to black
    SDL_RenderClear(renderer); //clears render color to screen
    SDL_Rect rect = {220, 230, 200, 20}; //text rect for "game over"
    SDL_RenderCopy(renderer, gameOverTexture, NULL, &rect); //renders the "game over" message
  }
  else //if player wins
  {
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
void gamelogic::processEvents()
{
  SDL_Event event;
  while (SDL_PollEvent(&event)) //polls events
  {
    switch (event.type)
    {
      case SDL_WINDOWEVENT_CLOSE: //if someone clicks x 
        if (window) //if window exists
        {
          SDL_DestroyWindow(window); //destroys window
          window = NULL; //window points to null
          isRunning = false; //sdl window no longer running
        }
        break;
      case SDL_KEYDOWN: //if a key is pressed
        switch(event.key.keysym.sym)
        {
          case SDLK_ESCAPE: //when esc is pressed
            isRunning = false; //sdl window no longer running
        }
        break;
      case SDL_QUIT:
        isRunning = false;
        break;
      default:
        break;
    }
  }
  state = SDL_GetKeyboardState(NULL); //gets keyboard state
  if (state[SDL_SCANCODE_Z] && reimu.getIsAlive() && game) //if reimu is shooting, alive, and the program is running in game mode
  {
    Mix_Volume(0, 50); //volume in channel 0 set to 50 
    Mix_PlayChannel(0, damage, 0); //damage sound played once in channel 0
    for (int i = 0; i < 4; i++)
    {
      bobj= new bullet; //allocates enough memory for bobj
      bulletList[i].push_back(bobj); //pushes bobj into list
      switch (i) //left most bullet set to reimu's position, rest are set to the right of it
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

//collision detection with rectangular hitboxes
int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2)
{
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}

//collision detection with circuluar hitboxes
int gamelogic::collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2)
{
  return !(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) > r1 + r2);
} 

//inititiates the enemy bullets
void gamelogic::initEnemyBullet(int i)
{
  double dx; //x component of direction
  double dy; //y component of direction
  enemybulletList.resize(numRings); //list holds this many bullet rings
  it2 = enemybulletList.begin(); //it2 points to beginning of enemy bullet list
  it3 = it2; //it3 points to it2
  advance(it2,i); //it2 advances by i (the ring number that is being fired) spots
  advance(it3, numRings - 1); //advances it3 so that it points to the last element of the list
  Mix_PlayChannel(-1, fire, 0); //plays fire sound in channel -1
  random = (rand() % 360) * M_PI/180; //offsets the direction of the ring being fired
  if (it2 == it3) //screen is "free" of all bullets when all rings are fired
  {
    clear = false;
  }
  enemybulletArray = new enemybullet*[SIZE]; //allocates memory to enemyBulletArray
  for (int index = 0; index < SIZE; index++)
  {
    //makes enemy bullets form a circl
    dx = cos((index * 2 * M_PI + random) / (SIZE));
    dy = sin((index * 2 * M_PI + random) / (SIZE));
    enemybulletArray[index] = new enemybullet(junko.getX(), junko.getY(), dx, dy); //enemy bullet position set and direction is set
  }
  enemybulletList.insert(it2, enemybulletArray); //inserts enemy bullet array into the enemy bullet list at the current iterator position
}

//clears reimu's bullets
void gamelogic::clearBullet()
{
  //clears reimu's bullets that leave the screen
  if (reimu.getIsAlive()) //if reimu is alive
  {
    for (int i = 0; i < 4; i++)
    {
      if (bulletList[i].size()) //checks if the array of bullet lists at index i is exists 
      {
        if (bulletList[i].front()) //checks if front exists
        {
          if (bulletList[i].front()->getY() <= 0) //deletes bullet that exits top of screen
          {
            delete bulletList[i].front();
            bulletList[i].pop_front();
          }
        }
      }
    }

    //clears bullets that collide with junko
    for (int i = 0; i < 4; i++)
    {
      for (it = bulletList[i].begin(); it != bulletList[i].end(); it++)
      {
        if (*it) //if iterator exists
        {
          if (collisionDetection(junko.getX(), junko.getY(), (*it)->getX(), (*it)->getY(), 49, 5)) //checks if bullet collides with junko
          {
            if (healthVector.size()) //checks if health bar exists
            {
              updateHealthBar(); //health bar updates
            }
            else
            {
              game = false; //game mode stops running
              success = true; //player wins
            }
            //deletes bullets that collide with junko
            delete (*it); 
            (*it) = NULL;
          }
        }
      }
    }
  }

  else //if reimu's dead
  {
    //all bullets get deleted
    for (int i = 0; i < 4; i++)
    {
      if (bulletList[i].size())
      {
        for (it = bulletList[i].begin(); it != bulletList[i].end(); it++)
        {
          delete *it;
          *it = NULL;
        }
        bulletList[i].erase(bulletList[i].begin(), bulletList[i].end());
      }
    }
  }
}

//updates position of all objects 
void gamelogic::update()
{
  static double dx = 1; //x component of velocity is 1
  if (reimu.getIsAlive())
  {

    //updates reimu's position
    reimu.update();

    //updates junko's position
    if (movement) //if junko is moving
    {
      if (junko.getX() > 450) //if junko reaches right edge direction is reversed
      {
        dx = -dx;
      }
      else if (junko.getX() < 0) //if junko reaches left edge direction is reversed
      {
        dx = -dx;
      }
      junko.updateX(dx); //calls junko's update direction function
    }

    //updates bullets position
    for (int i = 0; i < 4; i++)
    {
      for (it = bulletList[i].begin(); it!= bulletList[i].end(); it++)
      {
        if (*it) //checks if iterator exists
        {
          (*it)->updatePosition(); //updates position for current iterator
        }
      }
    }    

    //updates enemy bullets position
    for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++)
    {
      if (*it2) //checks if iterator exists
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j]) //checks if array exists
          {
            (*it2)[j]->updatePosition(); //updates all enemy bullets at the current iterator
          }
        }
      }
    }
  }
}

//updates the health bar if junko is shot
void gamelogic::updateHealthBar()
{
  if (junko.updateHp() % 7 == 0) //took mod of 7 because health is 7 * 410, 410 being the initial size of the vector
  {
    //removes a small health segment if multiples of 7 health are removed
    delete healthVector.back();
    healthVector.pop_back();
  }
}

//clears enemy bullet
void gamelogic::clearEnemyBullet()
{
  if (reimu.getIsAlive())
  {
    for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++)
    {
      if (*it2)
      {
        for (int j = 0; j < SIZE; j++)
        {
          if ((*it2)[j] != NULL)
          {
            if ((*it2)[j]->getX() < 0)
            {
              counter++; //counts bullets that exit the screen
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
              counter = 0; //counter set to 0 since rings are going to disappear
              Mix_PlayChannel(0, dead, 0); //plays dead sound in channel 0
              delete (*it2)[j];
              (*it2)[j] = NULL;
              reimu.setIsAlive(false); //reimu dies
              if (starVector.size()) //if the player has lives a star is removed
              {
                starVector.pop_back();
              }
              else //if there are no stars, then game over
              {
                game = false;
                gameOver = true;
              }
            }
          }
        }
      }
    }
    if (counter == numRings * SIZE) //if bullets passed is equal to amount of rings times the amount of bullets in each ring
    {
      //deletes all bullets
      for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++)
      {
        if (*it2)
        {
          delete *it2;
          *it2 = NULL;
        }
      }
      enemybulletList.clear(); //clears list
      counter = 0; //counter is equal to 0 since new set of rings about to get fired
      clear = true; //screen cleared
      setRings(++numRings); //number of rings in each set increases by 1
    }
  }
  else //if reimu's dead
  {
    //bullets get deleted
    for (it2 = enemybulletList.begin(); it2 != enemybulletList.end(); it2++)
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
        delete *it2;
        *it2 = NULL;
      }
    }
    enemybulletList.clear(); //clears list
    clear = true; //screen cleared
    reimu.setIsAlive(true); //reimu now alive
  }
}

//returns whether reimu's alive
bool gamelogic::getReimuState()
{
  return reimu.getIsAlive();
}

//things to do when game quits
void gamelogic::quit()
{
  //clears bullet array of lists
  for (int i = 0; i < 4; i++)
  {
    bulletList[i].clear();
  }

  //clears health bar
  for (unsigned int i = 0; i < healthVector.size(); i++)
  {
    delete healthVector[i];
  }
  IMG_Quit(); //quits image library
  SDL_Quit();
  //destroys textures
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
}
