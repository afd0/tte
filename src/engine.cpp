#define _XOPEN_SOURCE 700
#include "engine.h"
#include "main.h"
#include <string>
#include <ncurses.h>
#include <locale.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <termcolor/termcolor.hpp>

using namespace tte;

static const char * ESC = "\x1b[";

#define COLOR_BONE 10

void tte::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    clear();
    refresh();
    //color defs
    init_color(COLOR_BONE, 959, 924, 744);
    init_pair(1, COLOR_BONE, COLOR_BLACK);

    setlocale(LC_ALL, "");
    //nodelay(stdscr, true);
}

void engine::handleInput() {
    //char l = -1;
    //char ls = -1;
    e.type = -1;
    std::string c;
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
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
        //refresh();
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
    std::string command = ESC + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
    std::cout << command << text;
}

void engine::scrClear() {
    std::string command = ESC;
    command = command + "2J";
    std::cout << command;
}

void engine::printChar(int x, int y, char c) {
    std::string command = ESC + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
    std::cout << command << c;
}

void engine::printCharU(int x, int y, std::string c) {
    std::string command = ESC + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
    std::cout << command << c;
}

tte::box engine::drawBox(int x, int y, int w, int h, std::string title) {
    for (int i = y; i < y + h; i++) {
        printCharU(x, i, "│");
        printCharU(x + w - 1, i, "│");
    }
    for(int i = x; i < x + w; i++) {
        printCharU(i, y, "─");
        printCharU(i, y + h - 1, "─");
    }

    if (title != "") {
        printText(x + 3, y, title.c_str());
        printCharU(x + 2, y, "┤");
        printCharU(x + 3 + title.length(), y, "├");
    }

    printCharU(x, y, "╭");
    printCharU(x, y + h - 1, "╰");
    printCharU(x + w - 1, y, "╮");
    printCharU(x + w - 1, y + h - 1, "╯");
    
    tte::box box(x, y, w, h, title);
    return box;
}

void engine::getBounds(int &x, int &y) {
    int mx, my;
    getmaxyx(stdscr, my, mx);
    x = mx; y = my;
}

void engine::getCursorPos(int &x, int &y) {
    x = getcurx(stdscr);
    y = getcury(stdscr);
}

void box::printText(int tx, int ty, std::string text) {
    if (ty + y + 1 < y + h - 1) {
        if (text.size() > w - 2)
            text.resize(w - 2);
        engine::printText(tx + x + 1, ty + y + 1, text);
    }
}

void box::printChar(int tx, int ty, wchar_t c) {
    engine::printChar(tx + x + 1, ty + y + 1, c);
}

void box::clear() {
    for (int i = 0; i < w - 2; i++) {
        for (int j = 0; j < h - 2; j++) {
            engine::printCharU(i + x + 1, j + y + 1, " ");
        }
    }
}

void engine::changeColor(int r, int g, int b) {
    //ESC[38;2;{r};{g};{b}m
    std::string cl = "38;2;";
    std::string command = ESC + cl + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    std::cout << command;
}

void box::redraw() {
    engine::drawBox(x, y, w, h, title);
}