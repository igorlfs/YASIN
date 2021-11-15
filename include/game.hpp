#pragma once

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <string>

namespace game {

enum direction { VER, HOR };

static constexpr int BLANK{(int)' '};
static constexpr int PAUSE{(int)'p'};

class Game {
  public:
    Game(WINDOW *win);

    bool isOver() { return this->isGameOver; }
    void processInput();
    void update();
    void print();

  private:
    bool isGameOver{false};
    board::Board board;
    drawable::Snake snake;
    drawable::Food food;
    int input{KEY_RIGHT};
    direction dir{HOR};

    // Set drawables according to board's dimensions
    void spawnSnake();
    void spawnFood();

    int pause();
    void gameOver(const std::string &message);
};
} // namespace game
