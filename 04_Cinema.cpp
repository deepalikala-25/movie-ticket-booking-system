#pragma once

#include <string>
#include <vector>
#include "03_Screen.cpp"

class Cinema {
private:
    std::string name;
    // OOP Concept: Composition - Cinema owns its screens
    std::vector<Screen*> screens;

public:
    Cinema(std::string name) {
        this->name = name;
    }

    ~Cinema() {
        for (Screen* scr : screens) {
            delete scr;
        }
        screens.clear();
    }

    void addScreen(Screen* scr) {
        screens.push_back(scr);
    }

    std::string getName() const { return name; }
    const std::vector<Screen*>& getScreens() const { return screens; }
};
