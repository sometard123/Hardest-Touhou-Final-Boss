#include <non1loop.h>
#include <star.h>
#include <vector>
#include <SDL_stuff.h>
#include <reimu.h>
using namespace std;
class attacks {
  public:
    attacks();
    ~attacks();
    void sequence();
    void setLives(int amtLives);
    static void initBombStars();
    static void initStars();
    static SDL_Renderer *renderer;
    static SDL_Window *window;
    static vector <star *>starVector;
    static vector <star *>bombVector;
  private:
    static int lives;
};
