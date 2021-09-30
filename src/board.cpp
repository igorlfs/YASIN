#include "board.hpp"
using namespace board;
Board::Board(WINDOW *win)
    : gameWindow(win), yMax(win->_maxy), xMax(win->_maxx) {
    box(this->gameWindow, 0, 0);
    wrefresh(this->gameWindow);
    keypad(this->gameWindow, true);
    leaveok(this->gameWindow, true);
}
bool Board::boundaryCheck(const std::pair<int, int> &p) const {
    return (p.first <= 0 || p.first >= this->yMax - 1 || p.second <= 0 ||
            p.second >= this->xMax - 1);
}
void Board::print(const unsigned &y, const unsigned &x, const chtype &c) const {
    mvwaddch(this->gameWindow, y, x, c);
}
void Board::print(const std::pair<int, int> &p, const chtype &c) const {
    mvwaddch(this->gameWindow, p.first, p.second, c);
}
