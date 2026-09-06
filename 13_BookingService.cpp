#pragma once

#include <vector>
#include <string>
#include "05_Show.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"

class BookingService {
private:
    // OOP Concept: Aggregation - Coordinates collection of shows and active bookings
    std::vector<Show*> shows;
    std::vector<Booking*> bookings;

public:
    ~BookingService() {
        for (Booking* b : bookings) {
            delete b;
        }
        bookings.clear();
    }

    void addShow(Show* s) {
        shows.push_back(s);
    }

    const std::vector<Show*>& getShows() const {
        return shows;
    }

    Show* findShow(int showId) {
        for (Show* s : shows) {
            if (s->getShowId() == showId) return s;
        }
        return nullptr;
    }

    Booking* findBooking(const std::string& bookingId) {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) return b;
        }
        return nullptr;
    }

    // OOP Concept: Association - Customer and Payment interact ephemerally with the orchestrator[cite: 1]
    Booking* bookSeats(Customer* customer, Show* show, const std::vector<std::string>& seatNumbers, Payment* payment) {
        if (!show || seatNumbers.empty() || !payment) return nullptr;

        std::vector<ShowSeat*> selectedSeats;
        
        // Atomicity Check: Reject immediately if ANY seat is invalid or booked[cite: 1]
        for (const std::string& sNum : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(sNum);
            if (!ss || !ss->isAvailable()) {
                return nullptr;
            }
            selectedSeats.push_back(ss);
        }

        // Lock seats tentatively
        for (ShowSeat* ss : selectedSeats) {
            ss->book();
        }

        double total = PriceCalculator::calculateTotal(selectedSeats);

        // OOP Concept: Runtime Polymorphism - Dynamic method dispatch via Payment interface[cite: 1]
        bool paymentSuccess = payment->pay(total);

        if (!paymentSuccess) {
            // Rollback reserved seats on payment failure[cite: 1]
            for (ShowSeat* ss : selectedSeats) {
                ss->release();
            }
            return nullptr;
        }

        Booking* newBooking = new Booking(show, selectedSeats, customer, total);
        newBooking->confirm();
        bookings.push_back(newBooking);

        TicketPrinter::printTicket(newBooking);
        return newBooking;
    }

    bool cancelBooking(const std::string& bookingId) {
        Booking* b = findBooking(bookingId);
        if (!b || b->getStatus() != "CONFIRMED") return false;

        b->cancel();
        return true;
    }
};
