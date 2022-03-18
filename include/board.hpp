#pragma once

#include <ncurses.h>
#include <utility>

namespace board {
class Board {
  public:
    /// Constructors
    Board(WINDOW *win);

    /// Getters
    [[nodiscard]] int getX() const { return this->xMax - 1; }
    [[nodiscard]] int getY() const { return this->yMax - 1; }
    [[nodiscard]] int getSize() const {
        return (this->xMax - 1) * (this->yMax - 1);
    }
    WINDOW *getWin() { return this->gameWindow; }

    /// Operations
    [[nodiscard]] bool isOutOfBounds(const std::pair<int, int> &p) const;
    void print(const std::pair<int, int> &p, const chtype &c) const;

  private:
    WINDOW *gameWindow;
    int yMax, xMax;
};
} // namespace board
