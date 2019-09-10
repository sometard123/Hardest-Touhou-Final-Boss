#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <iostream>
#include <reimu.h>
#include <bullet.h>
#include <cmath>
#define WINX 450
#define WINY 480
using namespace std;

//contructor initializes position and hitbox position
reimu::reimu() {
  x = 320;
  y = 240;
  h.x = x + 29;
  h.y = y + 29;
  bulletObject = NULL;
  bobj = NULL;
}

reimu::~reimu() {
  for (int i = 0; i < 4; i++) {
    bulletList[i].clear();
  }
}

void reimu::initBomb() {
  if (isAlive && !bobj) {
    bobj = new reimuBomb(this);
  }
}

void reimu::destroyBomb() {
  if (bobj) {
    bobj->timer();
    if (bobj->getTime()> 150) {
      delete bobj;
      bobj = NULL;
    }
  }
}
void reimu::initBullets(Mix_Chunk *damage) {
  state = SDL_GetKeyboardState(NULL); //gets keyboard state
  if (state[SDL_SCANCODE_Z] && isAlive) {
    Mix_Volume(0, 50); //volume in channel 0 set to 50 
    Mix_PlayChannel(0, damage, 0); //damage sound played once in channel 0
    for (int i = 0; i < 4; i++) {
      bulletObject = new reimuBullet(); //allocates enough memory for bobj
      bulletList[i].push_back(bulletObject); //pushes bobj into list
      switch (i) {//left most bullet set to reimu's position, rest are set to the right of it
        case 0:
          bulletList[i].back()->setPosition(x + i * 20, y);
          break;
        case 1:
          bulletList[i].back()->setPosition(x + i * 20, y);
          break;
        case 2:
          bulletList[i].back()->setPosition(x + i * 20, y);
          break;
        case 3:
          bulletList[i].back()->setPosition(x + i * 20, y);
          break;
        default: break;
      }
    }
  }
}

void reimu::clearBullet() {
  for (int i = 0; i < 4; i++) {
    if (bulletList[i].size()) {//checks if the array of bullet lists at index i is exists
      if (bulletList[i].front()) {//checks if front exists
        if (bulletList[i].front()->getY() <= 0) {//deletes bullet that exits top of screen
          delete bulletList[i].front();
          bulletList[i].pop_front(); 
        }
      }
    }
  }
  if (!isAlive) {
    for (int i = 0; i < 4; i++) {
      for (it = bulletList[i].begin(); it != bulletList[i].end(); it++) {
        if (*it) {
          delete *it;
          *it = NULL;
        }
      }
      bulletList[i].clear();
    }
  }
}


//sets reimu's alive status
void reimu::setIsAlive(bool alive) {
  reimu::isAlive = alive;
}

//returns whether reimu is alive or dead
bool reimu::getIsAlive() {
  return reimu::isAlive;
}

//returns reimu and reimu's hitboxes position
double reimu::getX() {
  return x;
}

double reimu::getY() {
  return y;
}

double reimu::getHitboxX() {
  return h.x;
}

double reimu::getHitboxY() {
  return h.y;
}

bomb *reimu::getBomb() {
  return bobj;
}

//updates reimu's position
void reimu::update() {
  for (int i = 0; i < 4; i++) {
    for (it = bulletList[i].begin(); it != bulletList[i].end(); it++) {
      if (*it) {
        (*it)->updatePosition();
      }
    }
  }
  state = SDL_GetKeyboardState(NULL);

  if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) {//speed slowed when shift is pressed
    velocity = 1.5;
    diagonalVelocity = sqrt(pow(velocity,2) / 2.0);
    if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
      h.x -= diagonalVelocity;
      h.y -= diagonalVelocity;
      x -= diagonalVelocity;
      y -= diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
      h.x -= diagonalVelocity;
      h.y += diagonalVelocity;
      x -= diagonalVelocity;
      y += diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
      h.x += diagonalVelocity;
      h.y += diagonalVelocity;
      x += diagonalVelocity;
      y += diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
      h.x += diagonalVelocity;
      h.y -= diagonalVelocity;
      x += diagonalVelocity;
      y -= diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_LEFT]) {
      h.x -= velocity;
      x -= velocity;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
      h.x += velocity;
      x += velocity;
    }
    else if (state[SDL_SCANCODE_UP]) {
      h.y -= velocity;
      y -= velocity;
    }
    else if (state[SDL_SCANCODE_DOWN]) {
      h.y += velocity;
      y += velocity;
    }
  }
  else {
    velocity = 5.5;
    diagonalVelocity = sqrt(pow(velocity,2) / 2.0);
    if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {
      h.x -= diagonalVelocity;
      h.y -= diagonalVelocity;
      x -= diagonalVelocity;
      y -= diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_DOWN]) {
      h.x -= diagonalVelocity;
      h.y += diagonalVelocity;
      x -= diagonalVelocity;
      y += diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_DOWN]) {
      h.x += diagonalVelocity;
      h.y += diagonalVelocity;
      x += diagonalVelocity;
      y += diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
      h.x += diagonalVelocity;
      h.y -= diagonalVelocity;
      x += diagonalVelocity;
      y -= diagonalVelocity;
    }
    else if (state[SDL_SCANCODE_LEFT]) {
      h.x -= velocity;
      x -= velocity;
    }
    else if (state[SDL_SCANCODE_RIGHT]) {
      h.x += velocity;
      x += velocity;
    }
    else if (state[SDL_SCANCODE_UP]) {
      h.y -= velocity;
      y -= velocity;
    }
    else if (state[SDL_SCANCODE_DOWN]) {
      h.y += velocity;
      y += velocity;
    }
  }
  collisionDetection();
}

//collision detection with walls
void reimu::collisionDetection() {
  //reimu's position slightly bounces back when she hits a wall
  if (x + 64 > WINX) {
    x = WINX - 64;
    h.x = x + 29;
  }
  if (y + 64 > WINY) {
    y = WINY - 64;
    h.y = y + 29;
  }
  if (x < 0) {
    x = 0;
    h.x = x + 29;
  }
  if (y < 0) {
    y = 0;
    h.y = y + 29;
  }
}

void reimu::draw(SDL_Renderer *renderer, SDL_Texture *texture) {
  if (bobj) {
    bobj->draw(renderer);
  }
  SDL_Rect reimuRect = {(int)x, (int)y, 64, 64};
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderCopy(renderer, texture, NULL, &reimuRect);
  state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT]) {//displays hitbox when shift is pressed
    SDL_Rect hitboxRect = {(int)h.x, (int)h.y, 6, 6};
    SDL_RenderFillRect(renderer, &hitboxRect);
  }
  for (int i = 0; i < 4; i++) {
    for (it = bulletList[i].begin(); it != bulletList[i].end(); it++) {
      if (*it) {
        (*it)->draw(renderer);
      }
    }
  }
}
