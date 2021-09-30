#include "game.hpp"

// BUG: border's top left corner not drawing properly

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide cursor
    refresh();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(6, 6, (yMax / 2) - 2, (xMax / 2) - 2);
    game::Game snakeGame(gameWindow);
    halfdelay(5);
    while (!snakeGame.isOver()) {
        snakeGame.print();
        snakeGame.parseInput();
        snakeGame.move();
    }

    wgetch(gameWindow);
    delwin(gameWindow);
    endwin();
    return 0;
}
