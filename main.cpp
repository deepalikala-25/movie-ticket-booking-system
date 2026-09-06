#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

#include "01_Movie.cpp"
#include "02_Seat.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "05_Show.cpp"
#include "06_ShowSeat.cpp"
#include "07_Customer.cpp"
#include "08_Booking.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    // 1. Setup Cinema Domain Data
    Cinema pvr("PVR Cinemas");

    Screen* screen1 = new Screen("Screen-1");
    // Silver tier
    screen1->addSeat(new Seat("A1", "SILVER"));
    screen1->addSeat(new Seat("A2", "SILVER"));
    screen1->addSeat(new Seat("A3", "SILVER"));
    screen1->addSeat(new Seat("A4", "SILVER"));
    // Gold tier
    screen1->addSeat(new Seat("B1", "GOLD"));
    screen1->addSeat(new Seat("B2", "GOLD"));
    screen1->addSeat(new Seat("B3", "GOLD"));
    // Platinum tier
    screen1->addSeat(new Seat("C1", "PLATINUM"));
    screen1->addSeat(new Seat("C2", "PLATINUM"));

    Screen* screen2 = new Screen("Screen-2");
    screen2->addSeat(new Seat("A1", "SILVER"));
    screen2->addSeat(new Seat("B1", "GOLD"));

    pvr.addScreen(screen1);
    pvr.addScreen(screen2);

    Movie m1("3 Idiots", "Hindi", 170);
    Movie m2("Interstellar", "English", 169);

    Show show1(1, &m1, screen1, "06:00 PM");
    Show show2(2, &m1, screen2, "09:00 PM");
    Show show3(3, &m2, screen1, "09:30 PM");

    BookingService bookingService;
    bookingService.addShow(&show1);
    bookingService.addShow(&show2);
    bookingService.addShow(&show3);

    // Default Customer Context
    Customer guestCustomer("CUST101", "Guest Customer", "9876543210");

    // Interactive Console UI
    while (true) {
        std::cout << "\n===== MOVIE TICKET BOOKING =====\n";
        std::cout << "1. Movies  2. Book  3. Cancel  4. Exit\n";
        std::cout << "Choose: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "[!] Invalid input. Please enter a valid number.\n";
            clearCin();
            continue;
        }

        if (choice == 4) {
            std::cout << "Thank you for using PVR Cinemas. Goodbye!\n";
            break;
        }

        if (choice == 1) {
            std::cout << "\n[1] " << m1.getTitle() << " (" << m1.getLanguage() << " " << m1.getDuration() << " min)\n";
            std::cout << "[2] " << m2.getTitle() << " (" << m2.getLanguage() << " " << m2.getDuration() << " min)\n";
            continue;
        }

        if (choice == 2) {
            std::cout << "\nAvailable Movies:\n";
            std::cout << "[1] " << m1.getTitle() << "\n";
            std::cout << "[2] " << m2.getTitle() << "\n";
            std::cout << "Choose movie: ";
            int mChoice;
            std::cin >> mChoice;

            Movie* chosenMovie = (mChoice == 1) ? &m1 : ((mChoice == 2) ? &m2 : nullptr);
            if (!chosenMovie) {
                std::cout << "[!] Invalid movie selection.\n";
                continue;
            }

            std::cout << "\nAvailable Shows for " << chosenMovie->getTitle() << ":\n";
            std::vector<Show*> movieShows;
            for (Show* s : bookingService.getShows()) {
                if (s->getMovie()->getTitle() == chosenMovie->getTitle()) {
                    movieShows.push_back(s);
                    std::cout << "[" << movieShows.size() << "] " 
                              << s->getScreen()->getScreenNumber() << " " << s->getStartTime() << "\n";
                }
            }

            if (movieShows.empty()) {
                std::cout << "[!] No scheduled shows found.\n";
                continue;
            }

            std::cout << "Choose show: ";
            int sChoice;
            std::cin >> sChoice;
            if (sChoice < 1 || sChoice > static_cast<int>(movieShows.size())) {
                std::cout << "[!] Invalid show selection.\n";
                continue;
            }

            Show* selectedShow = movieShows[sChoice - 1];
            selectedShow->displaySeatLayout();

            std::cout << "\nEnter seats (comma separated, e.g. A1,B2): ";
            std::string seatLine;
            std::cin >> seatLine;

            std::vector<std::string> chosenSeats;
            std::stringstream ss(seatLine);
            std::string seatToken;
            while (std::getline(ss, seatToken, ',')) {
                if (!seatToken.empty()) chosenSeats.push_back(seatToken);
            }

            // Display breakdown
            double estimatedTotal = 0.0;
            bool validSelection = true;
            std::cout << "\n";
            for (const std::string& st : chosenSeats) {
                ShowSeat* seatObj = selectedShow->findShowSeat(st);
                if (!seatObj) {
                    std::cout << "[!] Seat " << st << " does not exist.\n";
                    validSelection = false;
                    break;
                }
                if (!seatObj->isAvailable()) {
                    std::cout << "[!] Seat " << st << " is ALREADY BOOKED. Selection aborted.\n";
                    validSelection = false;
                    break;
                }
                std::cout << seatObj->getSeatNumber() << " " << seatObj->getSeatType() 
                          << " Rs." << seatObj->getPrice() << "\n";
                estimatedTotal += seatObj->getPrice();
            }

            if (!validSelection) {
                std::cout << "[X] Booking rejected. No seats were reserved.\n";
                continue;
            }

            std::cout << "TOTAL: Rs." << estimatedTotal << "\n";

            std::cout << "Pay by: 1.UPI 2.Card 3.Cash > ";
            int payChoice;
            std::cin >> payChoice;

            // OOP Concept: Abstraction & Runtime Polymorphism - Base reference bound dynamically
            Payment* paymentMethod = nullptr;
            if (payChoice == 1) {
                paymentMethod = new UpiPayment("customer@okhdfc");
            } else if (payChoice == 2) {
                paymentMethod = new CardPayment("4111222233334444");
            } else if (payChoice == 3) {
                paymentMethod = new CashPayment();
            } else {
                std::cout << "[!] Invalid payment method. Transaction cancelled.\n";
                continue;
            }

            Booking* bResult = bookingService.bookSeats(&guestCustomer, selectedShow, chosenSeats, paymentMethod);
            delete paymentMethod;

            if (!bResult) {
                std::cout << "[!] Transaction failed. Booking was not confirmed.\n";
            }
        } else if (choice == 3) {
            std::cout << "Enter Booking ID to cancel (e.g. BK1001): ";
            std::string bId;
            std::cin >> bId;

            if (bookingService.cancelBooking(bId)) {
                std::cout << "[✓] Booking " << bId << " successfully CANCELLED. Seats are now AVAILABLE.\n";
            } else {
                std::cout << "[!] Failed to cancel booking. ID not found or already cancelled.\n";
            }
        } else {
            std::cout << "[!] Unknown option selected.\n";
        }
    }

    return 0;
}
