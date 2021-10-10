#include "game.hpp"

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide cursor
    refresh();

    if (!has_colors()) {
        printw("No color support");
        getch();
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Snake color
    init_pair(2, COLOR_RED, COLOR_BLACK);    // Food color

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(6, 6, (yMax / 2) - 2, (xMax / 2) - 2);
    game::Game snakeGame(gameWindow);
    halfdelay(5);
    while (!snakeGame.isOver()) {
        snakeGame.processInput();
        snakeGame.update();
        snakeGame.print();
    }

    wgetch(gameWindow);
    delwin(gameWindow);
    endwin();
    return 0;
}
