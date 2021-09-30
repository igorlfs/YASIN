#pragma once

#include "board.hpp"
#include "food.hpp"
#include "snake.hpp"
#include <string>

namespace game {

enum directions { VERTICAL, HORIZONTAL };

static constexpr int BLANK{(int)' '};

class Game {
  public:
    Game(WINDOW *win) : board(win), snake(board), food(board, snake) {}

    void move();
    void print();
    void parseInput();
    bool isOver() { return this->isGameOver; }

  private:
    bool isGameOver{false};
    board::Board board;
    drawable::Snake snake;
    drawable::Food food;
    int input{KEY_RIGHT};
    directions direction{HORIZONTAL};

    // Create a window and print a game over message
    void gameOver(const std::string &message);
};
} // namespace game
