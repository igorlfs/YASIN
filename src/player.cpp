#include "player.hpp"
#include <map>
#include <random>

// https://stackoverflow.com/a/13445752
namespace std {
int randomNumber(int ceiling) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist(1, ceiling);
    return dist(rng);
}
} // namespace std

using namespace Cobra;

cobra::cobra(WINDOW *win, const int &c) : currentWin(win), character(c) {
    getmaxyx(this->currentWin, this->yMax, this->xMax);
    keypad(this->currentWin, true);
    this->spawnCobra();
    this->spawnFood();
}
void cobra::spawnCobra() {
    for (int i = 0; i < this->initialSize; ++i)
        this->locations.push_back({this->yMax / 2 + i, this->xMax / 2});
}
void cobra::updateDirection(const int &input) {
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
void cobra::move() {
    pair<int, int> oldHead = this->locations.front();
    pair<int, int> newHead;
    switch (this->input) {
        case KEY_UP: newHead = {oldHead.first - 1, oldHead.second}; break;
        case KEY_DOWN: newHead = {oldHead.first + 1, oldHead.second}; break;
        case KEY_LEFT: newHead = {oldHead.first, oldHead.second - 1}; break;
        case KEY_RIGHT: newHead = {oldHead.first, oldHead.second + 1}; break;
    }
    if (boundaryCheck(newHead.first, newHead.second)) gameOver();
    pair<int, int> tail = this->locations.back();
    mvwaddch(this->currentWin, tail.first, tail.second, ' ');
    this->locations.pop_back();
}
void cobra::display() {
    for (auto i : this->locations)
        mvwaddch(this->currentWin, i.first, i.second, this->character);
}
void cobra::spawnFood() {
    do
        this->food = {std::randomNumber(this->yMax - 2),
                      std::randomNumber(this->xMax - 2)};
    while (isInsideCobra(this->food));
    mvwaddch(this->currentWin, this->food.first, this->food.second,
             this->foodChar);
}
bool cobra::isInsideCobra(const pair<int, int> &cell) const {
    for (auto i : this->locations)
        if (i == cell) return true;
    return false;
}
bool cobra::boundaryCheck(const int &m, const int &n) const {
    return (m <= 0 || m >= this->yMax - 1 || n <= 0 || n >= this->xMax - 1);
}
void cobra::gameOver() const {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameOver = newwin(3, 12, (yMax / 2) - 2, (xMax / 2) - 6);
    box(gameOver, 0, 0);
    refresh();
    mvwprintw(gameOver, 1, 1, "Game Over!");
    wgetch(gameOver);
    delwin(gameOver);
    endwin();
    std::exit(1);
}
