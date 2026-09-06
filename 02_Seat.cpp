#pragma once

#include <string>

class Seat {
private:
    std::string seatNumber;
    std::string seatType;        // SILVER, GOLD, or PLATINUM

public:
    Seat(std::string seatNumber, std::string seatType) {
        this->seatNumber = seatNumber;
        this->seatType = seatType;
    }

    std::string getSeatNumber() const { return seatNumber; }
    std::string getSeatType() const { return seatType; }
};
