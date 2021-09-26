#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include <ncurses.h>
using std::pair;
enum directions { VERTICAL, HORIZONTAL };
namespace Cobra {
class cobra {
  public:
    cobra(WINDOW *win, const int &c);
    void spawnCobra();

    void move();
    void updateDirection(const int &dir);
    void display();

    void spawnFood();
    bool isInsideCobra(const pair<int, int> &cell) const;

  private:
    static constexpr int initialSize{4};
    static constexpr int foodChar{(int)'$'};

    WINDOW *currentWin;
    int yMax, xMax;
    std::list<pair<int, int>> locations;
    pair<int, int> food;
    char character;
    int input{KEY_UP};
    directions direction{VERTICAL};
};
} // namespace Cobra
#endif
