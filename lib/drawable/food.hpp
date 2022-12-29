#pragma once

#include "drawable.hpp"

namespace drawable {
class Food : public Drawable {
  public:
    /// Constructors
    Food() {
        init_pair(2, COLOR_RED, -1);
        this->setChar(CHAR, 2);
    };

  private:
    static constexpr char CHAR = '$';
};
} // namespace drawable
