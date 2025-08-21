//#include <iostream>
//#include <ncurses.h>
//#include <random>
//#include <ctime>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "engine.h"

tte::engine engine;

std::string home_dir = getenv("HOME");
std::string active_project_dir = "";

// -- 0 == Main menu, 1 == Project view --
int mode = 0;

tte::box fileBox;
tte::box viewBox;
tte::box descBox;
tte::box planBox;

tte::box menuBox;

std::vector<std::string> fileNames;
std::vector<std::string> projects;
int selection = 0;

void drawProjectView(std::string path) {
    int maxX, maxY;
    engine.getBounds(maxX, maxY);

    fileBox = engine.drawBox(0, 0, maxX / 3, maxY, "Files");
    viewBox = engine.drawBox(maxX / 3, 0, maxX / 3, maxY / 2, "File preview");
    descBox = engine.drawBox(maxX / 3, maxY / 2, maxX / 3, maxY / 2 + 1, "Description");
    planBox = engine.drawBox(maxX / 3 * 2, 0, maxX / 3, maxY, "Plans&TODO");

    //std::string path = path;

    if (path.find("~/") != std::string::npos) {
        path = home_dir + "/" + path.substr(path.find("~/") + 2);
    }

    active_project_dir = path;

    for (const auto & entry : std::filesystem::recursive_directory_iterator(path)) {
        std::string p = entry.path();
        if (p.find(".dsc") == std::string::npos 
        &&  p.find(".pln") == std::string::npos
        &&  p.find(".vscode") == std::string::npos
        &&  p.find(".git") == std::string::npos) {
            p = p.substr(path.length());
            fileNames.push_back(p);
        }
    }

    for (int i = 0; i < fileNames.size(); i++) {
        fileBox.printText(1, i, fileNames[i]);
    }

    std::ifstream descFile(path + "/project.dsc");
    std::string line;
    int i = 0;
    while(getline(descFile, line)) {
        if (i < descBox.h)
            descBox.printText(0, i, line);
        i++;
    }

    std::ifstream planFile(path + "/project.pln");
    i = 0;
    while(getline(planFile, line)) {
        if (i < planBox.h)
            planBox.printText(0, i, line);
        i++;
    }
}

/*std::vector<std::string> loadProjectList() {
    std::ifstream plFile("~/projects.l");
    std::string line;
    std::vector<std::string> projects;
    while(getline(plFile, line)) {
        projects.push_back(line);
    }

    //return projects;
}*/

bool projectsLoaded = false;

void drawMainMenu() {
    int maxX, maxY;
    engine.getBounds(maxX, maxY);

    menuBox = engine.drawBox(maxX / 4, maxY / 4, maxX / 2, maxY / 2, "Select project");

    if (!projectsLoaded) {
        std::ifstream plFile(home_dir + "/projects.l");
        std::string line;
        //std::vector<std::string> projects;
        while(getline(plFile, line)) {
            projects.push_back(line);
        }
        projectsLoaded = true;
    }

    for (int i = 0; i < projects.size(); i++) {
        menuBox.printText(1, i, projects[i]);
    } 
}

void openProject(std::string path) {
    drawProjectView(path);
}

void update(tte::engine *engine) {
    // -- Handle input --
    if (engine->e.type != -1) {
        switch (engine->e.type) {
            case 'q':
                engine->shutdown();
                break;
            case 'i':
                if (mode == 1) {
                    if (selection > 0) {
                        fileBox.printChar(0, selection, ' ');
                        selection--;
                    }
                } else if (mode == 0) {
                    if (selection > 0) {
                        menuBox.printChar(0, selection, ' ');
                        selection--;
                    }
                }
                break;
            case 'k':
                if (mode == 1) {
                    if (selection < fileNames.size() - 1) {
                        fileBox.printChar(0, selection, ' ');
                        selection++;
                    }
                } else if (mode == 0) {
                    if (selection < projects.size() - 1) {
                        menuBox.printChar(0, selection, ' ');
                        selection++;
                    }
                }
                break;
            case '\n':
                if (mode == 1) {
                    viewBox.clear();
                    std::ifstream MyReadFile(active_project_dir + fileNames[selection]);
                    std::string line;
                    int i = 0;
                    while(getline(MyReadFile, line)) {
                        if (i < viewBox.h)
                            viewBox.printText(0, i, line);
                        i++;
                    }
                } else if (mode == 0) {
                    engine->scrClear();
                    mode = 1;
                    drawProjectView(projects[selection]);
                }
                break;
            case 27:
                engine->scrClear();
                mode = 0;
                drawMainMenu();
                break;
        }
        engine->e.type = -1;
    } else {
        
    }

    if (mode == 1)
        fileBox.printChar(0, selection, '>');
    else if (mode == 0)
        menuBox.printChar(0, selection, '>');
}

int main() {
    tte::init();

    int maxX, maxY;
    engine.getBounds(maxX, maxY);

    drawMainMenu();

    engine.run();
}