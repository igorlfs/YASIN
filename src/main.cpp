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
    use_default_colors();

    static constexpr int y = 12;
    static constexpr int x = 12;
    static constexpr int delay = 5;
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(y, x, (yMax - y) / 2, (xMax - x) / 2);
    game::Game snakeGame(gameWindow);
    halfdelay(delay);
    while (!snakeGame.isOver()) {
        snakeGame.processInput();
        snakeGame.update();
        snakeGame.print();
    }

    delwin(gameWindow);
    endwin();
}

void checkColor() {
    if (!has_colors()) {
        printw("No color support");
        getch();
        exit(1);
    }
}
