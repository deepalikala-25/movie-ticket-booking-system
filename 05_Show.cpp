#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "06_ShowSeat.cpp"

class Show {
private:
    int showId;
    // OOP Concept: Aggregation - Borrows Movie and Screen instances
    Movie* movie;
    Screen* screen;
    std::string startTime;
    // OOP Concept: Composition - Show strictly creates and owns its ShowSeats[cite: 1]
    std::vector<ShowSeat*> showSeats;

public:
    Show(int showId, Movie* movie, Screen* screen, std::string startTime) {
        this->showId = showId;
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;

        // Populate dynamic show seats from the screen layout with tiered pricing[cite: 1]
        for (Seat* physicalSeat : screen->getSeats()) {
            double basePrice = 150.0;
            if (physicalSeat->getSeatType() == "GOLD") {
                basePrice = 250.0;
            } else if (physicalSeat->getSeatType() == "PLATINUM") {
                basePrice = 400.0;
            }
            showSeats.push_back(new ShowSeat(physicalSeat, basePrice));
        }
    }

    ~Show() {
        for (ShowSeat* ss : showSeats) {
            delete ss;
        }
        showSeats.clear();
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    std::string getStartTime() const { return startTime; }
    const std::vector<ShowSeat*>& getShowSeats() const { return showSeats; }

    ShowSeat* findShowSeat(const std::string& seatNum) {
        for (ShowSeat* ss : showSeats) {
            if (ss->getSeatNumber() == seatNum) {
                return ss;
            }
        }
        return nullptr;
    }

    void displaySeatLayout() const {
        std::cout << "\n" << screen->getScreenNumber() << "  " << startTime << "  " << movie->getTitle() << "\n";
        
        std::string currentTier = "";
        for (ShowSeat* ss : showSeats) {
            if (ss->getSeatType() != currentTier) {
                currentTier = ss->getSeatType();
                std::cout << "\n" << std::left << std::setw(10) << currentTier << " ";
            }
            std::string marker = ss->isAvailable() ? "[]" : "[X]";
            std::cout << ss->getSeatNumber() << marker << " ";
        }
        std::cout << "\n([] = available, [X] = booked)\n";
    }
};
