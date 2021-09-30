#pragma once

#include "drawable.hpp"
#include <list>

namespace drawable {
class Snake : public Drawable {
  public:
    Snake(board::Board &board);

    std::pair<int, int> getTail() { return this->oldTail; }

    void setOldHead(const std::pair<int, int> &p) { this->oldHead = p; }

    std::list<std::pair<int, int>> getBody() { return this->body; }

    std::pair<int, int> changeHead(const int &input);
    void insertHead(const std::pair<int, int> &newHead);
    void removeTail();

    bool isInBody(const std::pair<int, int> &p) const;
    void print(const board::Board &board) const override;

  private:
    static constexpr char chBody = '#';
    static constexpr char chHead = '@';
    std::pair<int, int> oldHead;
    std::pair<int, int> oldTail;
    std::list<std::pair<int, int>> body;
};
} // namespace drawable
