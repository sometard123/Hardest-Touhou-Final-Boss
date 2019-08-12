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
    //constructor/deconstructor
    gamelogic();
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
    //getters

    bool getRunning();
    bool getReimuState();
    bool getClear();
    bool getLoading();
    bool getGame();
    bool getGameOver();
    int getRings();
    //init

    void initStars();
    void initHealthBar();
    void initWindow();
    void initEnemyBullet(int i);
    //draw

    void render();

    //collision detection

    int collisionDetection(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2);
    int collisionDetection(double x1, double y1, double x2, double y2, double r1, double r2);
    //clear

    void clearBullet();
    void clearEnemyBullet();
    void deleteBomb();
    //update

    void update();
    void updateHealthBar();
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

    SDL_Renderer *renderer;
    SDL_Window *window;
    //fonts

    TTF_Font *font;
};
