#include <bomb.h>
#include <iostream>

using namespace std;

//bomb timer initializes when bomb object is being constructed
bomb::bomb() {
  time = 0;
}

bomb::~bomb() {
}

//sets bomb position
void bomb::setPosition(double xcoord, double ycoord) {
  bombx = xcoord;
  bomby = ycoord;
}

//returns bomb damage area
double bomb::getDamageSize() {
  return size;
}

double bomb::getX() {
  return bombx;
}

double bomb::getY() {
  return bomby;
}

//returns bombs damage
double bomb::getDamage() {
  return damage;
}

//gets the time of the bomb
int bomb::getTime() {
  return time;
}

void bomb::timer() {
  time++;
}

