#include "engine.h"
#include "main.h"
#include <string>
#include <ncurses.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace tte;

void tte::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    clear();
    refresh();
    //nodelay(stdscr, true);
}

void engine::handleInput() {
    //char l = -1;
    //char ls = -1;
    e.type = -1;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
        //l = getch();
        //if (l != -1) { ls = l; }
        //e.type = ls; 
        //ls = -1;
        e.type = getch();
    }
}

void engine::run() {
    running = true;
    getmaxyx(stdscr, maxY, maxX);

    std::thread t1(&engine::handleInput, this);
    t1.detach();

    while (running) {
        update(this);
        refresh();
    }
    t1.join();
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

tte::box engine::drawBox(int x, int y, int w, int h, std::string title) {
    for (int i = y; i < y + h; i++) {
        printChar(x, i, '|');
        printChar(x + w - 1, i, '|');
    }
    for(int i = x; i < x + w; i++) {
        printChar(i, y, '=');
        printChar(i, y + h - 1, '=');
    }

    if (title != "") {
        title = ">" + title + "<";
        printText(x + 2, y, title.c_str());
    }

    printChar(x, y, 'O');
    printChar(x, y + h - 1, 'O');
    printChar(x + w - 1, y, 'O');
    printChar(x + w - 1, y + h - 1, 'O');

    tte::box box(x, y, w, h);
    return box;
}

void engine::getBounds(int &x, int &y) {
    int mx, my;
    getmaxyx(stdscr, my, mx);
    x = mx; y = my;
}

void box::printText(int tx, int ty, std::string text) {
    engine::printText(tx + x + 1, ty + y + 1, text);
}

void box::printChar(int tx, int ty, char c) {
    engine::printChar(tx + x + 1, ty + y + 1, c);
}