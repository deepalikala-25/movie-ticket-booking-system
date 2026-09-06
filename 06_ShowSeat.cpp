#pragma once

#include <string>
#include "02_Seat.cpp"

class ShowSeat {
private:
    // OOP Concept: Aggregation - Borrows reference to physical Seat without owning its lifetime
    Seat* physicalSeat;
    std::string status; // AVAILABLE, BOOKED
    double price;

public:
    ShowSeat(Seat* seat, double price) {
        this->physicalSeat = seat;
        this->price = price;
        this->status = "AVAILABLE";
    }

    // OOP Concept: Encapsulation - State transitions strictly handled via dedicated methods[cite: 1]
    bool isAvailable() const {
        return status == "AVAILABLE";
    }

    bool book() {
        if (!isAvailable()) return false;
        status = "BOOKED";
        return true;
    }

    void release() {
        status = "AVAILABLE";
    }

    std::string getSeatNumber() const { return physicalSeat->getSeatNumber(); }
    std::string getSeatType() const { return physicalSeat->getSeatType(); }
    double getPrice() const { return price; }
    std::string getStatus() const { return status; }
};
