#pragma once

#include <string>
#include <vector>
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"

class Booking {
private:
    // OOP Concept: Static Members - Generates unique monotonic booking identifiers
    static int nextBookingId;

    std::string bookingId;
    // OOP Concept: Aggregation - Borrows pointers to Show, ShowSeats, and Customer[cite: 1]
    Show* show;
    std::vector<ShowSeat*> bookedSeats;
    Customer* customer;
    double totalAmount;
    std::string status; // CREATED, CONFIRMED, CANCELLED, FAILED

public:
    Booking(Show* show, const std::vector<ShowSeat*>& seats, Customer* customer, double totalAmount) {
        this->bookingId = "BK" + std::to_string(++nextBookingId);
        this->show = show;
        this->bookedSeats = seats;
        this->customer = customer;
        this->totalAmount = totalAmount;
        this->status = "CREATED";
    }

    // OOP Concept: Compile-Time Polymorphism - Overloaded constructor[cite: 1]
    Booking(Show* show, const std::vector<ShowSeat*>& seats, double totalAmount) 
        : Booking(show, seats, nullptr, totalAmount) {}

    // OOP Concept: Encapsulation - Internal status modified only via dedicated transition methods[cite: 1]
    void confirm() {
        this->status = "CONFIRMED";
    }

    void markFailed() {
        this->status = "FAILED";
    }

    void cancel() {
        if (this->status == "CONFIRMED") {
            for (ShowSeat* ss : bookedSeats) {
                ss->release();
            }
            this->status = "CANCELLED";
        }
    }

    std::string getBookingId() const { return bookingId; }
    double getTotalAmount() const { return totalAmount; }
    std::string getStatus() const { return status; }
    Show* getShow() const { return show; }
    const std::vector<ShowSeat*>& getBookedSeats() const { return bookedSeats; }
};

// Initialize static identifier generator
int Booking::nextBookingId = 1000;
