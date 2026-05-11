#include "customer.h"
#include <iomanip>
#include <sstream>

Customer::Customer(int id, const std::string& name, const std::string& email, const std::string& phone, CustomerType type, double balance)
    : id(id), name(name), email(email), phone(phone), type(type), balance(balance) {}

void Customer::deposit(double amount) { balance += amount; }
bool Customer::withdraw(double amount) {
    if (balance < amount) return false;
    balance -= amount;
    return true;
}

void Customer::print(std::ostream& os) const {
    os << "ID:" << id << " | Ism: " << name << " | Balans: " << balance;
}

std::string Customer::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << name << "|" << email << "|" << phone << "|" << (int)type << "|" << balance;
    return oss.str();
}
