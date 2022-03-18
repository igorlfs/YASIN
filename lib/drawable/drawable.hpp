#pragma once

#include <ncurses.h>
#include <utility>

namespace drawable {
class Drawable {
  public:
    [[nodiscard]] chtype getChar() const { return this->character; }
    [[nodiscard]] std::pair<int, int> getHead() const { return this->head; }

    void setChar(const char &c, const int &n) {
        this->character = c | A_BOLD | COLOR_PAIR(n);
    }
    void setHead(const std::pair<int, int> &p) { this->head = p; }

  private:
    std::pair<int, int> head;
    chtype character;
};
} // namespace drawable
