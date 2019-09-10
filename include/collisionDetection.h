#include <reimu.h>
#include <junko.h>
#include <gamelogic.h>
class collisionDetection {
  public:
    collisionDetection();
    ~collisionDetection();
    bool collisionDetection2d(double x1, double y1, double x2, double y2, double wt1, double ht1, double wt2, double ht2);
    bool collisionDetection2d(double x1, double y1, double x2, double y2, double r1, double r2);
    void reimuBulletsWithJunko(reimu &reimuObject, junko &junkoObject, gamelogic &gobj);
    void reimuWithJunkoBullets(reimu &reimuObject, junko &junkoObject, gamelogic &gobj, Mix_Chunk *dead);
    void reimuBombWithJunkoBullets(reimu &reimuObject, junko &junkoObject, gamelogic &gobj);
    void reimuBombWithJunko(reimu &reimuObject, junko &junkoObject, gamelogic &gobj);
  private:
};
