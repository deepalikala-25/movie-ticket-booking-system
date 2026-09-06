#pragma once

#include <vector>
#include "06_ShowSeat.cpp"

// Single Responsibility Principle (SRP): pure pricing calculation service
class PriceCalculator {
public:
    static double calculateTotal(const std::vector<ShowSeat*>& seats) {
        double total = 0.0;
        for (const ShowSeat* seat : seats) {
            total += seat->getPrice();
        }
        return total;
    }
};
