#pragma once

#include <string>
#include <atomic>

namespace tte {

    void init();

    class box {
        public:
            int x, y, w, h;
            box(int xx, int yy, int ww, int hh) {
                x = xx; y = yy; w = ww; h = hh;
            }
            void printText(int tx, int ty, std::string text);
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
            void printChar(int x, int y, char c);
            box drawBox(int x, int y, int w, int h, std::string title);
            void getBounds(int &x, int &y);
            void clear();
    };
}