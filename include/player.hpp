#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include <ncurses.h>
using std::pair;
enum directions { UP, DOWN, LEFT, RIGHT };
namespace Cobra {
class cobra {
  public:
    cobra(WINDOW *win, const char &c);
    void spawnCobra();

    void move();
    void updateDirection(const int &dir);
    void display();

  private:
    static constexpr int initialSize{5};
    WINDOW *currentWin;
    int yMax, xMax;
    std::list<pair<int, int>> locations;
    char character;
    int input{KEY_UP};
    directions direction{UP};
};
} // namespace Cobra
#endif
