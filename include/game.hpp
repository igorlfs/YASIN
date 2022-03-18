#pragma once

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <string>

namespace game {

enum direction { VER, HOR };

class Game {
  public:
    Game(WINDOW *win);

    [[nodiscard]] bool isOver() const { return this->isGameOver; }
    void processInput();
    void update();
    void print();

  private:
    static constexpr int BLANK{(int)' '};
    static constexpr int PAUSE{(int)'p'};

    bool isGameOver{false};

    board::Board board;
    drawable::Snake snake;
    drawable::Food food;
    int input{KEY_RIGHT};
    direction dir{HOR};

    void spawnFood();

    int pause();
    void gameOver(const std::string &message);
};
} // namespace game
