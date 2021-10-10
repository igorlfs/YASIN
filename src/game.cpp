#include "game.hpp"

#include <map>
using namespace game;
Game::Game(WINDOW *win) : board(win), snake(board), food(board, snake) {
    for (auto i : this->snake.getBody())
        board.print(i, this->snake.getChar(), 1);
}
void Game::processInput() {
    int input = wgetch(this->board.getWin());
    std::map<int, directions> invalidMoves = {{KEY_UP, VERTICAL},
                                              {KEY_DOWN, VERTICAL},
                                              {KEY_LEFT, HORIZONTAL},
                                              {KEY_RIGHT, HORIZONTAL}};
    for (auto i = invalidMoves.begin(); i != invalidMoves.end(); ++i) {
        if (input == i->first && i->second != this->direction) {
            this->input = input;
            this->direction = i->second;
            return;
        }
    }
}
void Game::update() {
    std::pair<int, int> newHead = this->snake.changeHead(this->input);
    if (this->board.isOutOfBounds(newHead)) this->gameOver("DEFEAT!");
    // "Eat" by not removing tail
    if (newHead != this->food.getHead()) this->snake.removeTail();
    // You need to remove the tail before checking if the head is inside
    if (this->snake.isInBody(newHead)) this->gameOver("DEFEAT!");
    this->snake.insertHead(newHead);
    int snakeSize = this->snake.getBody().size() + 1; // size + head
    if (newHead == this->food.getHead() && snakeSize != this->board.getSize())
        this->food.spawn(this->board, this->snake);
    if (snakeSize == this->board.getSize()) this->gameOver("VICTORY!");
}
void Game::print() {
    this->board.print(this->snake.getOldTail(), BLANK, 0);
    this->board.print(this->food.getHead(), this->food.getChar(), 2);
    this->board.print(this->snake.getHead(), this->snake.getChar(), 1);
    wrefresh(this->board.getWin());
}
void Game::gameOver(const std::string &message) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int x = message.size() + 2; // Message + Borders
    WINDOW *gameOver = newwin(3, x, (yMax - 3) / 2, (xMax - x) / 2);
    box(gameOver, 0, 0);
    mvwprintw(gameOver, 1, 1, message.c_str());
    wgetch(gameOver);
    delwin(gameOver);
    this->isGameOver = true;
}
