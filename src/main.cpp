#include "game.hpp"
#include "msgassert.hpp"

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide cursor
    refresh();
    assert(has_colors(), "No color support");
    start_color();
    use_default_colors();

    static constexpr int HEIGHT = 6;
    static constexpr int WIDTH = 6;
    static constexpr int DELAY = 5;
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow =
        newwin(HEIGHT, WIDTH, (yMax - HEIGHT) / 2, (xMax - WIDTH) / 2);
    Game snake(gameWindow);
    halfdelay(DELAY);
    while (!snake.isOver()) {
        snake.processInput();
        snake.update();
        snake.print();
    }

    delwin(gameWindow);
    endwin();
}
