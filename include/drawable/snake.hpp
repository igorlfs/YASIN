#pragma once

#include "drawable.hpp"
#include <list>

namespace drawable {
class Snake : public Drawable {
  public:
    /// Constructors
    Snake(const int &boardX);

    /// Getters
    std::pair<int, int> getOldTail() { return this->oldTail; }
    std::list<std::pair<int, int>> getBody() { return this->body; }

    /// Setters
    void setOldHead(const std::pair<int, int> &p) { this->oldHead = p; }

    /// Modifiers
    std::pair<int, int> changeHead(const int &input);
    void insertHead(const std::pair<int, int> &newHead);
    void removeTail();

    /// Lookup
    bool isInBody(const std::pair<int, int> &p) const;
    bool isInSnake(const std::pair<int, int> &p) const;

  private:
    static constexpr int y = 1;
    static constexpr char ch = '@';
    std::pair<int, int> oldHead;
    std::pair<int, int> oldTail;
    std::list<std::pair<int, int>> body;
};
} // namespace drawable
