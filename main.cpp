//#include <iostream>
//#include <ncurses.h>
//#include <random>
//#include <ctime>
#include <string>
#include <vector>
#include "engine.h"
#include <filesystem>

tte::engine engine;

tte::box fileBox;
std::vector<std::string> fileNames;
int selection = 0;

void update(tte::engine *engine) {
    // -- Handle input --
    if (engine->e.type != -1) {
        switch (engine->e.type) {
            case 'q':
                engine->shutdown();
                break;
            case 'i':
                if (selection > 0)
                    fileBox.printChar(0, selection, ' ');
                    selection--;
                break;
            case 'k':
                if (selection < fileNames.size())
                    fileBox.printChar(0, selection, ' ');
                    selection++;
                break;
        }
        engine->e.type = -1;
    } else {
        
    }

    fileBox.printChar(0, selection, '>');

    //fileBox.printText(0, 2, "Apina");
}

int main() {
    tte::init();

    int maxX, maxY;
    engine.getBounds(maxX, maxY);

    fileBox = engine.drawBox(0, 0, maxX / 3, maxY, "Files");
    tte::box mainBox2 = engine.drawBox(maxX / 3, 0, maxX / 3, maxY / 2, "Main 2");
    tte::box mainBox3 = engine.drawBox(maxX / 3, maxY / 2, maxX / 3, maxY / 2 + 1, "Main 3");
    tte::box mainBox4 = engine.drawBox(maxX / 3 * 2, 0, maxX / 3, maxY, "Main 4");

    std::string path = "./";

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        fileNames.push_back(entry.path());
    }

    for (int i = 0; i < fileNames.size(); i++) {
        fileBox.printText(1, i, fileNames[i]);
    }

    mainBox2.printText(0, 0, "Testailua");
    mainBox3.printText(0, 0, "LLisää testailua");

    engine.run();
}