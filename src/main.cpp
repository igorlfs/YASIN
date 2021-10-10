#include "game.hpp"

void checkColor();

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide cursor
    refresh();
    checkColor();
    start_color();

    static constexpr int y = 6, x = 6;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(y, x, (yMax - y) / 2, (xMax - x) / 2);
    game::Game snakeGame(gameWindow);
    halfdelay(5);
    while (!snakeGame.isOver()) {
        snakeGame.processInput();
        snakeGame.update();
        snakeGame.print();
    }

    delwin(gameWindow);
    endwin();
    return 0;
}

void checkColor() {
    if (!has_colors()) {
        printw("No color support");
        getch();
        exit(1);
    }
}
