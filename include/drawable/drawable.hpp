#pragma once

#include "board.hpp"
#include <utility>

namespace drawable {
class Drawable {
  public:
    char getChar() const { return this->character; }
    std::pair<int, int> getHead() const { return this->head; }

    void setChar(const char &c) { this->character = c; }
    void setHead(const std::pair<int, int> &p) { this->head = p; }

    virtual void print(const board::Board &board) const = 0;

  private:
    std::pair<int, int> head;
    char character;
};
} // namespace drawable
