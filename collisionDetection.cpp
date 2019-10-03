#include <collisionDetection.h>
#include <cmath>
#include <stdbool.h>
#define SIZE 90
collisionDetection::collisionDetection() {
}

collisionDetection::~collisionDetection() {
}

bool collisionDetection::collisionDetection2d(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2) {
  return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}
bool collisionDetection::collisionDetection2d(double x1, double y1, double x2, double y2, double r1, double r2) {
  return !(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)) > r1 + r2);
}

void collisionDetection::reimuBulletsWithJunko(reimu &reimuObject, junko &junkoObject, gamelogic &gobj){
  if (reimuObject.getIsAlive()) {
    for (int i = 0; i < 4; i++) {
      for (reimuObject.it = reimuObject.bulletList[i].begin(); reimuObject.it != reimuObject.bulletList[i].end(); reimuObject.it++) {
        if (*(reimuObject.it)) {
          if (collisionDetection2d(junkoObject.getX(), junkoObject.getY(), (*(reimuObject.it))->getX(), (*(reimuObject.it))->getY(), 49, 5)) {
            delete *(reimuObject.it);
            *(reimuObject.it) = NULL;
            if (gobj.getHealthBar().size()) {
              gobj.updateHealthBar();
            }
            else {
              gobj.setGame(false);
              gobj.setSuccess(true);
              delete *(reimuObject.it);
              *(reimuObject.it) = NULL;
            }
          }
        }
      }
    }
  }
}

void collisionDetection::reimuWithJunkoBullets(reimu &reimuObject, junko &junkoObject, gamelogic &gobj, Mix_Chunk *dead) {
  for (junkoObject.it = junkoObject.bulletList.begin();  junkoObject.it != junkoObject.bulletList.end(); junkoObject.it++) {
    if (*junkoObject.it) {
      for (int i = 0; i < SIZE; i++) {
        if ((*junkoObject.it)[i]) {
          if (collisionDetection2d(reimuObject.getHitboxX()+3, reimuObject.getHitboxY()+3, (*junkoObject.it)[i]->getX()+(*junkoObject.it)[i]->getSize()/2, (*junkoObject.it)[i]->getY()+ (*junkoObject.it)[i]->getSize()/2,3, (*junkoObject.it)[i]->getSize()/2)) {
            Mix_PlayChannel(0, dead, 0); //plays dead sound in channel 0
            delete (*junkoObject.it)[i];
            (*junkoObject.it)[i] = NULL;
            junkoObject.setCounter(junkoObject.getCounter() + 1);
            reimuObject.setIsAlive(false);
            reimuObject.setPosition(320, 240);
            if (attacks::starVector.size()) {
              gobj.updateStars();
            }
            else {
              gobj.setGame(false);
              gobj.setGameOver(true);
            }
          }
        }
      }
    }
  }
} 
void collisionDetection::reimuBombWithJunkoBullets(reimu &reimuObject, junko &junkoObject, gamelogic &gobj) {
  for (junkoObject.it = junkoObject.bulletList.begin(); junkoObject.it != junkoObject.bulletList.end(); junkoObject.it++) {
    if (*junkoObject.it) {
      for (int i = 0; i < SIZE; i++) {
        if ((*junkoObject.it)[i] && reimuObject.getBomb()) {
          if (collisionDetection2d(reimuObject.getBomb()->getX()+150, reimuObject.getBomb()->getY()+150, (*junkoObject.it)[i]->getX() + 5, (*junkoObject.it)[i]->getY() + 5, 150, (*junkoObject.it)[i]->getSize() / 2)){
            delete (*junkoObject.it)[i];
            (*junkoObject.it)[i] = NULL;
            junkoObject.setCounter(junkoObject.getCounter()+ 1);
          }
        }
      }
    }
  }
}

void collisionDetection::reimuBombWithJunko(reimu &reimuObject, junko &junkoObject, gamelogic &gobj) {
  if (reimuObject.getBomb()){
    if (collisionDetection2d(reimuObject.getBomb()->getX(), reimuObject.getBomb()->getY(), junkoObject.getX(), junkoObject.getY(), 300, 300, 128, 64)) {
      for (int i = 0; i < reimuObject.getBomb()->getDamage(); i++) {
        if (gobj.getHealthBar().size()) {
          gobj.updateHealthBar();
        }
      }
    }
  }
}

void collisionDetection::reimuWithJunko(reimu &reimuObject, junko &junkoObject, gamelogic &gobj, Mix_Chunk *dead) {
  if (collisionDetection2d(reimuObject.getHitboxX(), reimuObject.getHitboxY(), junkoObject.getX(), junkoObject.getY(),6, 6, 128, 64)) {
    reimuObject.setIsAlive(false);
    reimuObject.setPosition(320, 240);
    Mix_PlayChannel(0, dead, 0); //plays dead sound in channel 0
    if (attacks::starVector.size()) {
      gobj.updateStars();
    }
    else {
      gobj.setGame(false);
      gobj.setGameOver(true);
    }
  }
}

