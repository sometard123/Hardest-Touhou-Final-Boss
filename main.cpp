#include <iostream>
#include <cstdlib>
#include <time.h>
#include <attacks.h>

using namespace std;

int main(int argc, char *argv[]) {
  //rng
  srand(time(NULL));
  attacks a;
  a.sequence();
  return EXIT_SUCCESS;
}
