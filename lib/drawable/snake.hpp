#pragma once

#include "drawable.hpp"
#include <list>

namespace drawable {
class Snake : public Drawable {
  public:
    /// Constructors
    Snake(const int &boardX);

    /// Getters
    [[nodiscard]] std::pair<int, int> getOldTail() const {
        return this->oldTail;
    }
    [[nodiscard]] std::list<std::pair<int, int>> getBody() const {
        return this->body;
    }
    [[nodiscard]] int getSize() const { return this->body.size() + 1; }

    /// Setters
    void setOldHead(const std::pair<int, int> &location) {
        this->oldHead = location;
    }

    /// Modifiers
    std::pair<int, int> changeHead(const int &input);
    void insertHead(const std::pair<int, int> &newHead);
    void removeTail();

    /// Lookup
    [[nodiscard]] bool isInBody(const std::pair<int, int> &location) const;
    [[nodiscard]] bool isInSnake(const std::pair<int, int> &location) const;

  private:
    static constexpr int HEIGHT = 1;
    static constexpr char CHAR = '#';
    std::pair<int, int> oldHead;
    std::pair<int, int> oldTail;
    std::list<std::pair<int, int>> body;
};
} // namespace drawable
