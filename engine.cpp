#include "engine.h"
#include "main.h"
#include <string>
#include <ncurses.h>
#include <iostream>

using namespace tte;

void tte::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    clear();
    refresh();
}

void engine::run() {
    running = true;
    getmaxyx(stdscr, maxY, maxX);
    while (running) {
        update(this);
        refresh();
    }
}

char engine::getCharacter() {
    return (getch());
}

int engine::shutdown() {
    running = false;
    endwin();
    exit(0);
    return 0;
}

void engine::printText(int x, int y, std::string text) {
    mvwprintw(stdscr, y, x, text.c_str());
}

void engine::clear() {
    clear();
}

void engine::printChar(int x, int y, char c) {
    mvwaddch(stdscr, y, x, c);
}

void engine::drawBox(int x, int y, int w, int h, std::string title) {
    for (int i = y; i < y + h; i++) {
        printChar(x, i, '|');
        printChar(x + w - 1, i, '|');
    }
    for(int i = x; i < x + w; i++) {
        printChar(i, y, '=');
        printChar(i, y + h - 1, '=');
    }

    title = ">" + title + "<";
    printText(x + 1, y, title.c_str());

    printChar(x, y, 'O');
    printChar(x, y + h - 1, 'O');
    printChar(x + w - 1, y, 'O');
    printChar(x + w - 1, y + h - 1, 'O');
}