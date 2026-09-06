#pragma once

#include <iostream>
#include <string>
#include "09_Payment.cpp"

// OOP Concept: Inheritance - UpiPayment inherits from abstract Payment
class UpiPayment : public Payment {
private:
    std::string vpaId;

public:
    UpiPayment(std::string vpaId) {
        this->vpaId = vpaId;
    }

    // OOP Concept: Runtime Polymorphism - Overrides pure virtual pay() method[cite: 1]
    bool pay(double amount) override {
        std::cout << "[UPI] Rs." << amount << " paid successfully via " << vpaId << "\n";
        return true;
    }
};

// OOP Concept: Inheritance - CardPayment inherits from abstract Payment[cite: 1]
class CardPayment : public Payment {
private:
    std::string cardNumber;

public:
    CardPayment(std::string cardNumber) {
        this->cardNumber = cardNumber;
    }

    bool pay(double amount) override {
        std::cout << "[Card] Rs." << amount << " charged to Card ending in " 
                  << cardNumber.substr(cardNumber.length() > 4 ? cardNumber.length() - 4 : 0) << "\n";
        return true;
    }
};

// OOP Concept: Inheritance - CashPayment inherits from abstract Payment[cite: 1]
class CashPayment : public Payment {
public:
    CashPayment() {}

    bool pay(double amount) override {
        std::cout << "[Cash] Rs." << amount << " collected in cash successfully.\n";
        return true;
    }
};
