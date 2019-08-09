#include <iostream>
#include <gameloop.h>
#include <cstdlib>
#include <time.h>
using namespace std;
int main(int argc, char *argv[])
{
  srand(time(NULL));
  gameloop *loop = new gameloop;
  loop->loop();
  delete loop;
  return EXIT_SUCCESS;
}
