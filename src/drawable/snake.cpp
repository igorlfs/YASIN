#include "snake.hpp"
using namespace drawable;
Snake::Snake(board::Board &board) {
    setChar(chHead);
    setHead({1, board.getX() / 2});
    for (int i = 1; i < board.getX() / 2; ++i) this->body.push_front({1, i});
}
bool Snake::isInBody(const std::pair<int, int> &p) const {
    for (auto i : this->body)
        if (p == i) return true;
    return false;
}
std::pair<int, int> Snake::changeHead(const int &input) {
    setOldHead(getHead());
    switch (input) {
        case KEY_UP: setHead({getHead().first - 1, getHead().second}); break;
        case KEY_DOWN: setHead({getHead().first + 1, getHead().second}); break;
        case KEY_LEFT: setHead({getHead().first, getHead().second - 1}); break;
        case KEY_RIGHT: setHead({getHead().first, getHead().second + 1}); break;
    }
    return getHead();
}
void Snake::insertHead(const std::pair<int, int> &newHead) {
    this->setHead(newHead);
    this->body.push_front(this->oldHead);
}
void Snake::removeTail() {
    this->oldTail = this->body.back();
    this->body.pop_back();
}
void Snake::print(const board::Board &board) const {
    board.print(this->getHead(), this->getChar());
    for (auto i : this->body) board.print(i, this->chBody);
}
