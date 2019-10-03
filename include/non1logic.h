#pragma once
#include <stdbool.h>
#include <reimu.h>
#include <healthbar.h>
#include <vector>
#include <star.h>
#include <attacks.h>
#include <SDL_stuff.h>
using namespace std;
class gamelogic {
  public:
    //constructor/deconstructor
    gamelogic();
    gamelogic(reimu);
    ~gamelogic();
    //setters

    void setLives(int amtLives);
    void setLoading(bool load);
    void setGame(bool md);
    void setGameOver(bool gmeOver);
    void setSuccess(bool win);
    void setTime(int tm);
    void setRings(int rings);
    void setRunning(bool running);
    void setJunkoMovement(bool mvt);
    void setClear(bool clr);
    void setReimuState(bool alive);
    //getters

    bool getRunning();
    bool getReimuState();
    bool getClear();
    bool getLoading();
    bool getGame();
    bool getGameOver();
    int getTime();
    int getRings();
    vector<healthbar *>getHealthBar();
    vector<star *>getStars();
    vector<star *>getBombStars();
    //init

    void initStars();
    void initBombStars();
    void initHealthBar();
    void initWindow();
    void initEnemyBullet(int i, gamelogic &gobj);
    //draw

    void render();

    //collision detection

    int collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2);
    int collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2);
    void handleCollisions(gamelogic &gobj);
    void handleBullets();
    void handleBomb();

    //clear

    void clearEnemyBullet(gamelogic &gobj);
    void deleteBomb();
    //update

    void update();
    void updateHealthBar();
    void updateStars();
    //quit

    void quit();
    //misc

    void processEvents();
    int timer();
  private:
    int random;
    bool isRunning;
    bool clear;
    bool loading;
    bool game;
    bool gameOver;
    bool success;
    bool movement;
    int counter;
    int numRings;
    const Uint8 *state;
    int time;
    int lives;
    //textures

    SDL_Texture *reimuTexture;
    SDL_Texture *playerTexture;
    SDL_Texture *bombTexture;
    SDL_Texture *starTexture;
    SDL_Texture *junkoTexture;
    SDL_Texture *loadingTexture;
    SDL_Texture *gameOverTexture;
    SDL_Texture *successTexture;
    //sounds

    Mix_Chunk *dead;
    Mix_Chunk *fire;
    Mix_Chunk *damage;
    Mix_Chunk *bombsound;
    //renderer/window

//    SDL_Renderer *renderer;
 //   SDL_Window *window;
    //fonts

    TTF_Font *font;
    vector<healthbar *> healthVector;
    vector<star *>starVector;
    vector<star *>bombVector;
};
