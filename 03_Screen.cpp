#pragma once

#include <string>
#include <vector>
#include "02_Seat.cpp"

class Screen {
private:
    std::string screenNumber;
    // OOP Concept: Composition - Screen owns its physical seats
    std::vector<Seat*> physicalSeats;

public:
    Screen(std::string screenNumber) {
        this->screenNumber = screenNumber;
    }

    ~Screen() {
        for (Seat* s : physicalSeats) {
            delete s;
        }
        physicalSeats.clear();
    }

    void addSeat(Seat* s) {
        physicalSeats.push_back(s);
    }

    std::string getScreenNumber() const { return screenNumber; }
    const std::vector<Seat*>& getSeats() const { return physicalSeats; }
};
