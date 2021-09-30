#pragma once

#include <ncurses.h>
#include <utility>

namespace board {
class Board {
  public:
    Board(WINDOW *win);

    int getX() { return this->xMax - 1; }
    int getY() { return this->yMax - 1; }
    int getSize() { return (this->xMax - 1) * (this->yMax - 1); }
    WINDOW *getWin() { return this->gameWindow; }

    bool isOutOfBounds(const std::pair<int, int> &p) const;

    void print(const unsigned &y, const unsigned &x, const chtype &c) const;
    void print(const std::pair<int, int> &p, const chtype &c) const;

  private:
    WINDOW *gameWindow;
    int yMax, xMax;
};
} // namespace board
