#include <iostream>
#include <gameloop.h>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
  //rng
  srand(time(NULL));
  gameloop *loop = new gameloop;
  loop->loop(); //calls game loop
  delete loop;
  return EXIT_SUCCESS;
}
