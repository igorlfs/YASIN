#include "snake.hpp"
#include "msgassert.hpp"
#include <algorithm>

using namespace drawable;

using std::pair;

Snake::Snake(const int &boardX) {
    init_pair(1, COLOR_GREEN, -1);
    this->setChar(CHAR, 1);
    const int LENGTH = boardX / 2;
    this->setHead({Snake::HEIGHT, LENGTH});
    for (int i = 1; i < LENGTH; ++i) {
        this->body.push_front({Snake::HEIGHT, i});
    }
}

pair<int, int> Snake::changeHead(const int &input) {
    setOldHead(getHead());
    switch (input) {
        case KEY_UP: setHead({getHead().first - 1, getHead().second}); break;
        case KEY_DOWN: setHead({getHead().first + 1, getHead().second}); break;
        case KEY_LEFT: setHead({getHead().first, getHead().second - 1}); break;
        case KEY_RIGHT: setHead({getHead().first, getHead().second + 1}); break;
    }
    return getHead();
}

void Snake::insertHead(const pair<int, int> &newHead) {
    this->setHead(newHead);
    this->body.push_front(this->oldHead);
}

void Snake::removeTail() {
    assert(!this->body.empty(), "Snake has empty body");
    this->oldTail = this->body.back();
    this->body.pop_back();
}

bool Snake::isInBody(const pair<int, int> &location) const {
    auto compare = [&location](const pair<int, int> &rhs) {
        return rhs == location;
    };
    return any_of(this->body.begin(), this->body.end(), compare);
}

bool Snake::isInSnake(const pair<int, int> &location) const {
    return (this->isInBody(location) || location == this->getHead());
}
