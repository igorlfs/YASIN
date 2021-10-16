#pragma once

#include "drawable.hpp"

namespace drawable {
class Food : public Drawable {
  public:
    Food() {
        init_pair(2, COLOR_RED, COLOR_BLACK);
        this->setChar(ch, 2);
    };

  private:
    static constexpr char ch = '$';
};
} // namespace drawable
