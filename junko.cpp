#include <junko.h>
#include <iostream>
#define SIZE 25
#define WINY 480
using namespace std;

//constructor initiates position and health
junko::junko() {
  x = 330;
  y = 100;
  health = 2870;
  numRings = 1000;
  bulletArray = NULL;
  time = 0;
}

junko::~junko() {
}

int junko::timer() {
  time++;
  return time;
}

void junko::setCounter(int cnt) {
  counter = cnt;
}

int junko::getCounter() {
  return counter;
}

//returns junko's xcoordinate
int junko::getX() {
  return x;
}

//returns junko's y coordinate
int junko::getY() {
  return y;
}

//updates x position with given velocity
void junko::updateX(double dx) {
  x += dx;
}

void junko::updateBullets() {
  for (it = bulletList.begin(); it != bulletList.end(); it++) {
    if (*it) {
      for (int i = 0; i < SIZE; i++) {
        if ((*it)[i]) {
          (*it)[i]->updatePosition();
        }
      }
    }
  }
}
void junko::initBullets(gamelogic &gobj, int i, Mix_Chunk *fire) {
  double dx;
  double dy;
  it = bulletList.begin();
  it2 = it;
  advance(it, i);
  advance(it2, numRings - 1);
  Mix_PlayChannel(-1, fire, 0);
  int random = (rand() % 360) * M_PI/180;
  bulletArray = new junko::junkoBullet*[SIZE];
  for (int j = 0; j < SIZE; j++) {
    dx = cos((j * 2 * M_PI + random) / (SIZE));
    dy = sin((j * 2 * M_PI - random) / (SIZE));
    bulletArray[j] = new junko::junkoBullet(x, y, dx, dy); //enemy bullet position set and direction is set
  }
  bulletList.push_back(bulletArray);
}

//updates health
int junko::updateHp() {
  return --health;
}

void junko::clearBullets(gamelogic &gobj) {
  if (gobj.getReimuState()) {
    for (it = bulletList.begin(); it != bulletList.end(); it++) {
      if (*it) {
        for (int j = 0; j < SIZE; j++) {
          if ((*it)[j]) {
            if ((*it)[j]->getX() < 0) {
              counter++; //counts bullets that exit the screen
              delete (*it)[j];
              (*it)[j] = NULL;
            } 
            else if ((*it)[j]->getX() > 450) {
              counter++;
              delete (*it)[j];
              (*it)[j] = NULL;
            }
            else if ((*it)[j]->getY() < 0) {
              counter++;
              delete (*it)[j];
              (*it)[j] = NULL;
            }
            else if ((*it)[j]->getY() > WINY) {
              counter++;
              delete (*it)[j];
              (*it)[j] = NULL;
            }
          }
        }
      }
      if (counter == gobj.getRings() * SIZE) { //deletes all bullets
        cout << "garbage" << endl;
        for (it = bulletList.begin(); it != bulletList.end(); it++) {
          if (*it) {
            delete []*it;
            *it = NULL;
          }
        }
        bulletList.clear();
        counter = 0;
        gobj.setClear(true);
        gobj.setRings(gobj.getRings()+1);
      }
    }
  }
  else {
    for (it = bulletList.begin(); it != bulletList.end(); it++) {
      if (*it) {
        for (int j = 0; j < SIZE; j++) {
          if ((*it)[j]) {
            counter++;
            delete (*it)[j];
            (*it)[j] = NULL;
          }
        }
        delete []*it;
        *it = NULL;
      }
    }
    gobj.setClear(true);
    bulletList.clear(); //clears list
    if (timer() > 50) {
      gobj.setReimuState(true); //reimu now alive
      time = 0;
    }
    gobj.setTime(0);
  }
}
//draws junko
void junko::draw(SDL_Renderer *renderer, SDL_Texture *texture) {
  int w;
  int h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h); //gets width and height from texture
  //resized width and height to appropriate size
  w /= 4;
  h /= 4;
  SDL_Rect JunkoRect = {x- 49, y - 62, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &JunkoRect);
  for (it = bulletList.begin(); it != bulletList.end(); it++) {
    if (*it) {
      for (int i = 0; i < SIZE; i++) {
        if ((*it)[i]) {
          (*it)[i]->draw(renderer);
        }
      }
    }
  }
}
