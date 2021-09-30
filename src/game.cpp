#include "game.hpp"
#include <map>
using namespace game;
void Game::parseInput() {
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
void Game::move() {
    std::pair<int, int> newHead = this->snake.changeHead(this->input);
    if (this->board.isOutOfBounds(newHead)) this->gameOver("DEFEAT!");
    // "Eat" by not removing tail
    if (newHead != this->food.getHead()) this->snake.removeTail();
    // You need to remove the tail before checking if the head is inside
    if (this->snake.isInBody(newHead)) this->gameOver("DEFEAT!");
    this->snake.insertHead(newHead);
    int snakeSize = this->snake.getBody().size() + 1;
    if (newHead == this->food.getHead() && snakeSize != this->board.getSize())
        this->food.spawn(this->board, this->snake);
    if (snakeSize == this->board.getSize()) this->gameOver("VICTORY!");
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
void Game::print() {
    this->board.print(this->snake.getTail(), BLANK);
    this->food.print(this->board);
    this->snake.print(this->board);
    wrefresh(this->board.getWin());
}
