#pragma once

// OOP Concept: Abstraction - Pure abstract base class defining payment contract
class Payment {
public:
    virtual ~Payment() {}
    // Pure virtual method for runtime polymorphism[cite: 1]
    virtual bool pay(double amount) = 0;
};
