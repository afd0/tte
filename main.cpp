//#include <iostream>
//#include <ncurses.h>
//#include <random>
//#include <ctime>
#include <string>
#include "engine.h"

void update(tte::engine *engine) {
    char c;
    c = engine->getCharacter();
    std::string s(1, c);
    if (c == 'q') { engine->shutdown(); }
    else { 
        engine->printText(1, 1, s);
        engine->printChar(2, 2, c);
    }
}

int main() {
    tte::init();

    tte::engine engine;

    engine.drawBox(0, 0, 3, 3, "a");

    engine.run();
}