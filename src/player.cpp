#include "player.hpp"
#include <curses.h>
#include <map>
#include <random>
#include <vector>

// https://stackoverflow.com/a/13445752
namespace std {
int randomNumber(const int &floor, const int &ceiling) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(floor, ceiling);
    return dist(rng);
}
} // namespace std

using namespace Cobra;

cobra::cobra(WINDOW *win, const int &c) : board(win), character(c) {
    this->spawnCobra();
    this->spawnFood();
}
void cobra::spawnCobra() {
    clear();
    for (int i = 0; i < this->board.getX() / 4 + 1; ++i) {
        this->locations.push_front({1, i + this->board.getX() / 4});
        board.print(1, i + this->board.getX() / 4, this->character);
    }
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
    pair<int, int> newHead = this->changeHead();
    if (this->board.boundaryCheck(newHead)) {
        this->gameOver("YOU LOST!");
        return;
    } // "Eat" by not removing tail
    if (newHead != this->food) {
        board.print(this->locations.back(), BLANK);
        this->locations.pop_back();
    } // You need to remove the tail before checking if the head is inside
    if (isInsideCobra(newHead)) {
        this->gameOver("YOU LOST!");
        return;
    }
    this->locations.push_front(newHead);
    if (newHead == this->food && this->locations.size() != board.getSize())
        this->spawnFood();
    if (this->locations.size() == board.getSize()) {
        this->gameOver("YOU WON!");
        return;
    }
    board.print(this->locations.front(), this->character);
}
std::pair<int, int> cobra::changeHead() {
    pair<int, int> head = this->locations.front();
    switch (this->input) {
        case KEY_UP: head = {head.first - 1, head.second}; break;
        case KEY_DOWN: head = {head.first + 1, head.second}; break;
        case KEY_LEFT: head = {head.first, head.second - 1}; break;
        case KEY_RIGHT: head = {head.first, head.second + 1}; break;
    }
    return head;
}
void cobra::spawnFood() {
    std::vector<pair<int, int>> positions;
    for (int i = 1; i <= this->board.getY(); ++i)
        for (int j = 1; j <= this->board.getX(); ++j) {
            pair<int, int> pair = {i, j};
            if (!isInsideCobra(pair)) positions.push_back(pair);
        }
    int index = std::randomNumber(0, positions.size() - 1);
    this->food = positions[index];
    this->board.print(this->food, this->foodChar);
}
bool cobra::isInsideCobra(const pair<int, int> &cell) const {
    for (auto i : this->locations)
        if (i == cell) return true;
    return false;
}
void cobra::gameOver(const std::string &message) {
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
