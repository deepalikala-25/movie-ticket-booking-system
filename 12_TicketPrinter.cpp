#pragma once

#include <iostream>
#include "08_Booking.cpp"

// Single Responsibility Principle (SRP): formatting and printing tickets only
class TicketPrinter {
public:
    static void printTicket(const Booking* b) {
        if (!b) return;
        std::cout << "\n================= TICKET =================" << "\n";
        std::cout << "Booking ID : " << b->getBookingId() << "\n";
        std::cout << "Movie      : " << b->getShow()->getMovie()->getTitle() << "\n";
        std::cout << "Screen     : " << b->getShow()->getScreen()->getScreenNumber() 
                  << " " << b->getShow()->getStartTime() << "\n";
        std::cout << "Seats      : ";
        const auto& seats = b->getBookedSeats();
        for (size_t i = 0; i < seats.size(); ++i) {
            std::cout << seats[i]->getSeatNumber() << (i + 1 < seats.size() ? ", " : "");
        }
        std::cout << "\nAmount     : Rs." << b->getTotalAmount() << "\n";
        std::cout << "Status     : " << b->getStatus() << "\n";
        std::cout << "==========================================" << "\n";
    }
};
