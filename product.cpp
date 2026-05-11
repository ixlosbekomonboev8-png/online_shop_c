#include "product.h"
#include <iomanip>
#include <sstream>

Product::Product(int id, const std::string& name, double price, int quantity, Category category)
    : id(id), name(name), price(price), quantity(quantity), category(category), unit("dona") {}

void Product::addStock(int amount) { quantity += amount; }
bool Product::removeStock(int amount) {
    if (quantity < amount) return false;
    quantity -= amount;
    return true;
}

void Product::print(std::ostream& os) const {
    os << "[" << std::setw(3) << id << "] " << std::setw(20) << std::left << name << " | Narx: " << price << " | Miqdor: " << quantity;
}

std::string Product::serialize() const {
    std::ostringstream oss;
    oss << getTypeId() << "|" << id << "|" << name << "|" << price << "|" << quantity;
    return oss.str();
}
