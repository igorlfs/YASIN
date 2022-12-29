#include "game.hpp"
#include "random.hpp"

#include <map>

using std::map;
using std::pair;
using std::string;
using std::vector;

/// @brief create game placing food and the snake
Game::Game(WINDOW *win) : board(win), snake(this->board.getX()) {
    this->spawnFood();
    this->board.print(this->snake.getHead(), this->snake.getChar());
    for (const auto &part : this->snake.getBody()) {
        board.print(part, this->snake.getChar());
    }
    this->board.print(this->food.getHead(), this->food.getChar());
}
/// @brief handle user input and update members accordingly
void Game::processInput() {
    int inputChar = wgetch(this->board.getWin());
    if (inputChar == PAUSE) {
        inputChar = this->pause();
    }
    const map<int, direction> INVALID_MOVES = {
        {KEY_UP, VER}, {KEY_DOWN, VER}, {KEY_LEFT, HOR}, {KEY_RIGHT, HOR}};
    for (const auto &invalidMove : INVALID_MOVES) {
        if (inputChar == invalidMove.first && invalidMove.second != this->dir) {
            this->input = inputChar;
            this->dir = invalidMove.second;
            return;
        }
    }
}

/// @brief process input and change game accordingly
void Game::update() {
    const pair<int, int> NEW_HEAD = this->snake.changeHead(this->input);
    if (this->board.isOutOfBounds(NEW_HEAD)) {
        this->gameOver("DEFEAT!");
    }
    // "Eat" by not removing tail
    if (NEW_HEAD != this->food.getHead()) {
        this->snake.removeTail();
    }
    // You need to remove the tail before checking if the head is inside
    if (this->snake.isInBody(NEW_HEAD)) {
        this->gameOver("DEFEAT!");
    }
    this->snake.insertHead(NEW_HEAD);
    // Check if game is won
    if (this->snake.getSize() == this->board.getSize()) {
        this->gameOver("VICTORY!");
        return;
    }
    if (NEW_HEAD == this->food.getHead()) {
        this->spawnFood();
    }
}

/// @brief print to stdscr changes made in the board
void Game::print() {
    this->board.print(this->snake.getOldTail(), BLANK);
    this->board.print(this->food.getHead(), this->food.getChar());
    this->board.print(this->snake.getHead(), this->snake.getChar());
    wrefresh(this->board.getWin());
}

/// @brief randomly generate food following available positions
/// (avalable positions do not contain the snake)
void Game::spawnFood() {
    vector<pair<int, int>> validPositions;
    for (int i = 1; i <= this->board.getY(); ++i) {
        for (int j = 1; j <= this->board.getX(); ++j) {
            if (!this->snake.isInSnake({i, j})) {
                validPositions.emplace_back(i, j);
            }
        }
    }
    const int INDEX = Random::rng(0, validPositions.size() - 1);
    this->food.setHead(validPositions[INDEX]);
}

/// @brief interrupt game's flow until pause key is pressed again
/// @return first non-pause input
int Game::pause() {
    bool shouldUnpause = false;
    do {
        const int READ = wgetch(this->board.getWin());
        if (READ == PAUSE) {
            shouldUnpause = true;
        }
    } while (!shouldUnpause);
    return wgetch(this->board.getWin());
}

/// @brief print a game over message and set state to gameOver
/// @param custom message to display
void Game::gameOver(const string &message) {
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);
    const int LENGTH = message.size() + 2; // Message + Borders
    WINDOW *gameOver = newwin(3, LENGTH, (yMax - 3) / 2, (xMax - LENGTH) / 2);
    nocbreak(); // Disables half-delay mode
    box(gameOver, 0, 0);
    mvwprintw(gameOver, 1, 1, "%s", message.c_str());
    wgetch(gameOver);
    delwin(gameOver);
    this->isGameOver = true;
}
