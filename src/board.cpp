#include "board.hpp"
using namespace board;
Board::Board(WINDOW *win)
    : gameWindow(win), yMax(win->_maxy), xMax(win->_maxx) {
    box(this->gameWindow, 0, 0);
    wrefresh(this->gameWindow);
    keypad(this->gameWindow, true);
    leaveok(this->gameWindow, true);
}
bool Board::isOutOfBounds(const std::pair<int, int> &p) const {
    return (p.first <= 0 || p.first >= this->yMax || p.second <= 0 ||
            p.second >= this->xMax);
}
void Board::print(const std::pair<int, int> &p, const chtype &c,
                  const int &n) const {
    wattron(this->gameWindow, COLOR_PAIR(n));
    mvwaddch(this->gameWindow, p.first, p.second, c);
    wattroff(this->gameWindow, COLOR_PAIR(n));
}
