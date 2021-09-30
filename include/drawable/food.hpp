#pragma once

#include "drawable.hpp"
#include "snake.hpp"

namespace drawable {
class Food : public Drawable {
  public:
    Food(board::Board &board, const Snake &snake);
    void spawn(board::Board &board, const Snake &snake);
    void print(const board::Board &board) const override;

  private:
    static constexpr char ch = '$';
};
} // namespace drawable
