#include "board.hpp"

Board::Board(WINDOW *win)
    : gameWindow(win), yMax(win->_maxy), xMax(win->_maxx) {
    box(this->gameWindow, 0, 0);
    wrefresh(this->gameWindow);
    keypad(this->gameWindow, true);
    leaveok(this->gameWindow, true);
}

bool Board::isOutOfBounds(const std::pair<int, int> &location) const {
    return (location.first <= 0 || location.first >= this->yMax ||
            location.second <= 0 || location.second >= this->xMax);
}

void Board::print(const std::pair<int, int> &location,
                  const chtype &cha) const {
    mvwaddch(this->gameWindow, location.first, location.second, cha);
}
