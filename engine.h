#pragma once

#include <string>

namespace tte {

    void init();

    class engine {
            bool running;
        public:
            int maxX, maxY;
            void run();
            char getCharacter();
            int shutdown();
            void printText(int x, int y, std::string text);
            void printChar(int x, int y, char c);
            void drawBox(int x, int y, int w, int h, std::string title);
            void clear();
    };
}