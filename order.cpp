#include "order.h"
#include <iomanip>
#include <sstream>

Order::Order(int id, int customerId, double discountRate, const std::string& createdAt)
    : id(id), customerId(customerId), status(OrderStatus::PENDING), discountRate(discountRate), createdAt(createdAt) {}

void Order::addItem(Product* product, int quantity) {
    items.push_back(OrderItem(product, quantity, product->getPrice()));
}

double Order::getTotal() const {
    double sub = 0;
    for (const auto& i : items) sub += i.subtotal();
    return sub * (1.0 - discountRate) * (1.0 + TAX_RATE);
}

void Order::print(std::ostream& os) const {
    os << "Buyurtma ID:" << id << " | Jami: " << getTotal();
}

std::string Order::serialize() const {
    std::ostringstream oss;
    oss << id << "|" << customerId << "|" << (int)status << "|" << discountRate << "|" << createdAt << "|";
    for (size_t i = 0; i < items.size(); ++i) {
        oss << items[i].product->getId() << ":" << items[i].quantity << ":" << items[i].unitPrice;
        if (i < items.size() - 1) oss << ",";
    }
    return oss.str();
}
