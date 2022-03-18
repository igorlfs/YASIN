#pragma once

#include "drawable.hpp"

namespace drawable {
class Food : public Drawable {
  public:
    Food() {
        init_pair(2, COLOR_RED, COLOR_BLACK);
        this->setChar(CH, 2);
    };

  private:
    static constexpr char CH = '$';
};
} // namespace drawable
