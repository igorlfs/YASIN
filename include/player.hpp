#ifndef PLAYER_H
#define PLAYER_H
#include <list>
#include <ncurses.h>
#include <string>
using std::pair;

namespace Cobra {

enum directions { VERTICAL, HORIZONTAL };

static constexpr int BLANK{(int)' '};

class cobra {
  public:
    cobra(WINDOW *win, const int &c);

    void move();
    void updateDirection(const int &dir);
    bool isOver() { return this->isGameOver; }

  private:
    static constexpr int foodChar{(int)'$'};

    WINDOW *currentWin;
    bool isGameOver{false};
    int yMax, xMax;
    std::list<pair<int, int>> locations;
    pair<int, int> food;
    char character;
    int input{KEY_RIGHT};
    directions direction{HORIZONTAL};

    void spawnCobra();

    void spawnFood();
    bool isInsideCobra(const pair<int, int> &cell) const;

    pair<int, int> changeHead();
    bool boundaryCheck(const int &m, const int &n) const;

    // Create a window and print a game over message
    void gameOver(const std::string &message);
};
} // namespace Cobra
#endif
