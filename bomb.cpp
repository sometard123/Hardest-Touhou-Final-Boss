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
  x = xcoord;
  y = ycoord;
}

//returns bomb damage area
double bomb::getDamageSize() {
  return size;
}

double bomb::getX() {
  return x;
}

double bomb::getY() {
  return y;
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
  cout << time << endl;
  time++;
}

