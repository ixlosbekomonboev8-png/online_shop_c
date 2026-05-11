#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "shop_types.h"
#include <string>
#include <iostream>

class Customer {
    int          id;
    std::string  name;
    std::string  email;
    std::string  phone;
    CustomerType type;
    double       balance;

public:
    Customer(int id, const std::string& name, const std::string& email, const std::string& phone, CustomerType type = CustomerType::REGULAR, double balance = 0.0);
    virtual ~Customer() = default;

    int          getId()      const { return id; }
    std::string  getName()    const { return name; }
    std::string  getEmail()   const { return email; }
    std::string  getPhone()   const { return phone; }
    double       getBalance() const { return balance; }

    void deposit(double amount);
    bool withdraw(double amount);
    bool canAfford(double amount) const { return balance >= amount; }
    double getDiscountRate() const { return (type == CustomerType::VIP) ? DISCOUNT_VIP : DISCOUNT_REGULAR; }
    bool isVIP() const { return type == CustomerType::VIP; }

    virtual void print(std::ostream& os = std::cout) const;
    std::string serialize() const;
};

#endif // CUSTOMER_H
