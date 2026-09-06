#pragma once

#include <string>

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string phone;

public:
    // OOP Concept: this Keyword - Resolves ambiguity between fields and parameters
    Customer(std::string customerId, std::string name, std::string phone) {
        this->customerId = customerId;
        this->name = name;
        this->phone = phone;
    }

    // OOP Concept: Encapsulation - Read-only getters[cite: 1]
    std::string getCustomerId() const { return customerId; }
    std::string getName() const { return name; }
    std::string getPhone() const { return phone; }
};
