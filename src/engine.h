#pragma once

#include <string>
#include <atomic>
#include <ncurses.h>

namespace tte {

    void init();

    class box {
        public:
            int x, y, w, h;
            std::string title;
            box(int xx, int yy, int ww, int hh, std::string text) {
                x = xx; y = yy; w = ww; h = hh; title = text;
            }
            box() {

            }
            void printText(int tx, int ty, std::string text);
            void printChar(int cx, int cy, wchar_t c);
            void clear();
            void redraw();
    };

    class inputEvent {
        public:
            std::atomic<int> resetCounter;
            std::atomic<char> type;
            char inputBuffer[10];
            inputEvent() {
                resetCounter = 0;
                type = -1;
            }
    };

    class engine {
            std::atomic<bool> running;
            void handleInput();
        public:
            int maxX, maxY;
            inputEvent e;
            void run();
            char getCharacter();
            int shutdown();
            static void printText(int x, int y, std::string text);
            static void printChar(int x, int y, char c);
            static void printCharU(int x, int y, std::string c);
            static box drawBox(int x, int y, int w, int h, std::string title);
            void getBounds(int &x, int &y);
            void getCursorPos(int &x, int &y);
            void scrClear();
            static void changeColor(int r, int g, int b);
    };
}