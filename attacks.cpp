#include <attacks.h>

SDL_Renderer *attacks::renderer = NULL;
SDL_Window *attacks::window = NULL;
vector <star *> attacks::starVector;
vector <star *>attacks::bombVector;
reimu ro;
int attacks::lives;
attacks::attacks() {
  if (!SDL_Init(0)) {
    TTF_Init();
    attacks::window= SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0); //creates window at any location with dimensions 640 by 480 called test
    attacks::renderer = SDL_CreateRenderer(attacks::window, -1, 0);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096); //initializes SDL_Mixer
  }
}

void attacks::setLives(int amtLives) {
  lives = amtLives;
}

void attacks::initBombStars() { //creates bomb stars
  attacks::bombVector.resize(lives);
  for (unsigned int i = 0; i < attacks::bombVector.size(); i++) {
    attacks::bombVector[i] = new star;
    attacks::bombVector[i]->setPosition(520 + 30 * i, 100);
  }
}

void attacks::initStars() {
  attacks::starVector.resize(lives);
  for (unsigned int i = 0; i < attacks::starVector.size(); i++) {
    attacks::starVector[i] = new star;
    attacks::starVector[i]->setPosition(520 + 30 * i, 50);
  }
}

void attacks::sequence() {
  setLives(3);
  attacks::initBombStars();
  attacks::initStars();
  non1loop non1;
  non1.loop();
}


attacks::~attacks() {
  for (unsigned int i = 0; i < attacks::bombVector.size(); i++) {
    delete bombVector[i];
  }
  for (unsigned int i = 0; i < attacks::starVector.size(); i++) {
    delete starVector[i];
  }
  SDL_Quit();
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}

