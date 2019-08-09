#pragma once
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <reimu.h>
class gamelogic
{
  public:
    gamelogic();
    ~gamelogic();
    //setters
    void setLives(int);
    void setLoading(bool);
    void setGame(bool);
    void setGameOver(bool);
    void setSuccess(bool);
    void setTime(int);
    void setRings(int);
    void setRunning(bool running);
    void setJunkoMovement(bool mvt);
    bool getRunning();
    bool getReimuState();
    bool getClear();
    bool getLoading();
    bool getGame();
    bool getGameOver();
    int getRings();
    void initStars();
    void initHealthBar();
    void initWindow(Mix_Chunk **);
    void render();
    void processEvents();
    int timer();
    int collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2);
    int collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2);
    void clearBullet();
    void updateEnemy();
    void updateHealthBar();
    void clearEnemy(Mix_Chunk **effect);
    void genEnemy(int i);
    void quit(Mix_Chunk **effect);
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
    int counter2;
    int numRings;
    reimu r;
    const Uint8 *state;
    int time;
    int lives;
    SDL_Texture *reimuTexture;
    SDL_Texture *playerTexture;
    SDL_Texture *starTexture;
    SDL_Texture *junkoTexture;
    SDL_Texture *loadingTexture;
    SDL_Texture *gameOverTexture;
    SDL_Texture *successTexture;
    SDL_Renderer *renderer;
    Mix_Chunk *fire;
    Mix_Chunk *damage;
    SDL_Window *window;
    TTF_Font *font;
};
