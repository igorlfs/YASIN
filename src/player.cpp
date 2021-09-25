#include "player.hpp"
#include <map>
#include <random>

// https://stackoverflow.com/a/13445752
namespace std {
int randomNumber(int ceiling) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(0, ceiling);
    return dist(rng);
}
} // namespace std

using namespace Cobra;

cobra::cobra(WINDOW *win, const char &c) : currentWin(win), character(c) {
    getmaxyx(this->currentWin, this->yMax, this->xMax);
    keypad(this->currentWin, true);
    this->spawnCobra();
}
void cobra::spawnCobra() {
    for (int i = 0; i < this->initialSize; ++i)
        this->locations.push_back({this->yMax / 2 + i, this->xMax / 2});
}
void cobra::updateDirection(const int &input) {
    std::map<int, directions> invalidMoves = {
        {KEY_UP, DOWN}, {KEY_DOWN, UP}, {KEY_LEFT, RIGHT}, {KEY_RIGHT, LEFT}};
    for (auto i = invalidMoves.begin(); i != invalidMoves.end(); ++i) {
        if (input == i->first && i->second != this->direction) {
            this->input = input;
            this->direction = i->second;
        }
    }
}
void cobra::move() {
    pair<int, int> oldHead = this->locations.front();
    pair<int, int> newHead;
    switch (this->input) {
        case KEY_UP: newHead = {oldHead.first - 1, oldHead.second}; break;
        case KEY_DOWN: newHead = {oldHead.first + 1, oldHead.second}; break;
        case KEY_LEFT: newHead = {oldHead.first, oldHead.second - 1}; break;
        case KEY_RIGHT: newHead = {oldHead.first, oldHead.second + 1}; break;
    }
    this->locations.push_front(newHead);
    pair<int, int> tail = this->locations.back();
    mvwaddch(this->currentWin, tail.first, tail.second, ' ');
    this->locations.pop_back();
}
void cobra::display() {
    for (auto i : this->locations)
        mvwaddch(this->currentWin, i.first, i.second, this->character);
}
