#pragma once

#include "drawable.hpp"
#include "snake.hpp"

namespace drawable {
class Food : public Drawable {
  public:
    /// Constructors
    Food(board::Board &board, const Snake &snake);

    /// Operations
    void spawn(board::Board &board, const Snake &snake);

  private:
    static constexpr char ch = '$';
};
} // namespace drawable
