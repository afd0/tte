//#include <iostream>
//#include <ncurses.h>
//#include <random>
//#include <ctime>
#include <string>
#include "engine.h"

void update(tte::engine *engine) {
    // -- Handle input --
    if (engine->e.type != -1) {
        if (engine->e.type == 'q') { engine->shutdown(); }
        else { engine->printChar(1, 1, engine->e.type); }
    } else {
        engine->printChar(1, 1, 'T');
    }
}

int main() {
    tte::init();

    tte::engine engine;

    int maxX, maxY;
    engine.getBounds(maxX, maxY);

    tte::box mainBox = engine.drawBox(0, 0, maxX / 3, maxY, "Main");
    tte::box mainBox2 = engine.drawBox(maxX / 3, 0, maxX / 3, maxY / 2, "Main 2");
    tte::box mainBox3 = engine.drawBox(maxX / 3, maxY / 2, maxX / 3, maxY / 2 + 1, "Main 3");
    tte::box mainBox4 = engine.drawBox(maxX / 3 * 2, 0, maxX / 3, maxY, "Main 4");

    mainBox.printText(0, 0, "Testi 1");
    mainBox.printText(0, 5, "Testi 2");

    mainBox2.printText(0, 0, "Testailua");
    mainBox3.printText(0, 0, "LLisää testailua");

    engine.run();
}