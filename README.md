# Movie Ticket Booking System (TCS-504)

A modular, console-based cinema ticket booking engine implemented in C++ adhering strictly to Object-Oriented Programming (OOP) and SOLID design principles.

---

## 1. Class Diagram

```mermaid
classDiagram
    direction TB

    class Cinema {
        -string name
        -vector~Screen*~ screens
        +Cinema(string name)
        +addScreen(Screen* s) void
        +getScreens() vector~Screen*~
    }

    class Screen {
        -string screenNumber
        -vector~Seat*~ physicalSeats
        +Screen(string num)
        +addSeat(Seat* s) void
        +getSeats() vector~Seat*~
        +getScreenNumber() string
    }

    class Seat {
        -string seatNumber
        -string seatType
        +Seat(string num, string type)
        +getSeatNumber() string
        +getSeatType() string
    }

    class Movie {
        -string title
        -string language
        -int durationMin
        +Movie(string t, string l, int d)
        +getTitle() string
        +getLanguage() string
        +getDuration() int
    }

    class Show {
        -int showId
        -Movie* movie
        -Screen* screen
        -string startTime
        -vector~ShowSeat*~ showSeats
        +Show(int id, Movie* m, Screen* s, string time)
        +getShowSeats() vector~ShowSeat*~
        +getMovie() Movie*
        +getScreen() Screen*
        +getStartTime() string
        +displaySeatLayout() void
    }

    class ShowSeat {
        -Seat* physicalSeat
        -string status
        -double price
        +ShowSeat(Seat* seat, double p)
        +isAvailable() bool
        +book() bool
        +release() void
        +getSeatNumber() string
        +getSeatType() string
        +getPrice() double
    }

    class Customer {
        -string customerId
        -string name
        -string phone
        +Customer(string id, string n, string p)
        +getName() string
        +getPhone() string
    }

    class Booking {
        -string bookingId
        -Show* show
        -vector~ShowSeat*~ bookedSeats
        -double totalAmount
        -string status
        -static int nextBookingId
        +Booking(Show* s, vector~ShowSeat*~ seats, double amount)
        +confirm() void
        +cancel() void
        +getBookingId() string
        +getTotalAmount() double
        +getStatus() string
        +getShow() Show*
        +getBookedSeats() vector~ShowSeat*~
    }

    class Payment {
        <<abstract>>
        +pay(double amount)* bool
    }

    class UpiPayment {
        -string vpaId
        +UpiPayment(string vpa)
        +pay(double amount) bool
    }

    class CardPayment {
        -string cardNumber
        +CardPayment(string card)
        +pay(double amount) bool
    }

    class CashPayment {
        +CashPayment()
        +pay(double amount) bool
    }

    class PriceCalculator {
        +calculateTotal(vector~ShowSeat*~ seats)$ double
    }

    class TicketPrinter {
        +printTicket(Booking* b)$ void
    }

    class BookingService {
        -vector~Show*~ availableShows
        -vector~Booking*~ bookings
        +addShow(Show* show) void
        +findShow(int showId) Show*
        +processBooking(Customer* c, Show* s, vector~string~ seatNums, Payment* p) Booking*
        +cancelBooking(string bookingId) bool
        +getBooking(string bookingId) Booking*
    }

    Cinema "1" *-- "1..*" Screen : owns
    Screen "1" *-- "1..*" Seat : contains
    Show "1" o-- "1" Movie : projects
    Show "1" o-- "1" Screen : hosted in
    Show "1" *-- "1..*" ShowSeat : creates per screening
    ShowSeat "1" o-- "1" Seat : references

    Booking "1" o-- "1" Show : books for
    Booking "1" o-- "1..*" ShowSeat : reserves
    Booking "1" --> "1" Customer : placed by

    BookingService "1" o-- "0..*" Show : manages
    BookingService "1" o-- "0..*" Booking : records
    BookingService ..> PriceCalculator : uses
    BookingService ..> TicketPrinter : uses
    BookingService ..> Payment : processes with

    Payment <|-- UpiPayment : inherits
    Payment <|-- CardPayment : inherits
    Payment <|-- CashPayment : inherits
```

---

## 2. Sequence Diagram (Booking & UPI Payment)

```mermaid
sequenceDiagram
    autonumber
    actor Customer
    participant BookingService
    participant Show
    participant ShowSeat
    participant PriceCalculator
    participant UpiPayment as Payment (UpiPayment)
    participant Booking
    participant TicketPrinter

    Customer ->> BookingService: processBooking(cust, show, ["A1"], upiPayObj)
    activate BookingService

    BookingService ->> Show: getShowSeats()
    activate Show
    Show -->> BookingService: return list of ShowSeat*
    deactivate Show

    loop Validate Seats
        BookingService ->> ShowSeat: isAvailable()
        activate ShowSeat
        ShowSeat -->> BookingService: true
        deactivate ShowSeat
    end

    BookingService ->> PriceCalculator: calculateTotal([ShowSeat A1])
    activate PriceCalculator
    PriceCalculator -->> BookingService: totalAmount (150.0)
    deactivate PriceCalculator

    BookingService ->> ShowSeat: book()
    activate ShowSeat
    ShowSeat -->> BookingService: true (Status: BOOKED)
    deactivate ShowSeat

    BookingService ->> UpiPayment: pay(150.0)
    activate UpiPayment
    UpiPayment -->> BookingService: true (Payment Confirmed)
    deactivate UpiPayment

    BookingService ->> Booking: <<create>>(show, [ShowSeat A1], 150.0)
    activate Booking
    Booking ->> Booking: confirm()
    Booking -->> BookingService: newBooking Instance
    deactivate Booking

    BookingService ->> TicketPrinter: printTicket(newBooking)
    activate TicketPrinter
    TicketPrinter -->> Customer: Displays formatted ASCII Ticket
    deactivate TicketPrinter

    BookingService -->> Customer: return Booking* confirmation
    deactivate BookingService
```

---

## 3. SOLID Principles Application

1. **Single Responsibility Principle (SRP):** `Booking` manages booking state; ticket formatting is handled by `TicketPrinter`, and tier calculations are isolated in `PriceCalculator`.
2. **Open/Closed Principle (OCP):** Adding new payment methods requires a new subclass of `Payment` without modifying existing booking workflows[cite: 1].
3. **Dependency Inversion Principle (DIP):** High-level `BookingService` depends on the abstract `Payment` contract rather than concrete payment types[cite: 1].

---

## 4. Compilation & Execution

```bash
# Compile
g++ -std=c++11 main.cpp -o cinema_app

# Run
./cinema_app
```
