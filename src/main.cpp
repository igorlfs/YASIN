#include "player.hpp"
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0); // Hide cursor

    if (!has_colors()) return 1; // use assert?

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(18, 24, (yMax / 2) - 9, (xMax / 2) - 12);
    box(gameWindow, 0, 0);
    refresh();
    wrefresh(gameWindow);
    /* mvprintw((yMax / 2) + 9, (xMax / 2) - 12, "Score:"); */

    std::unique_ptr<Cobra::cobra> p =
        std::make_unique<Cobra::cobra>(gameWindow, '@');

    std::thread play([&p, &gameWindow]() {
        while (1) {
            p->display();
            p->move();
            wrefresh(gameWindow);
            std::this_thread::sleep_for(333ms);
        }
    });
    while (1) {
        int input = wgetch(gameWindow);
        p->updateDirection(input);
    }

    delwin(gameWindow);
    getch();
    endwin();
    return 0;
}
