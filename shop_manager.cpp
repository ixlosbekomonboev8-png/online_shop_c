#include "shop_manager.h"
#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>

ShopManager::ShopManager()
    : nextCustomerId(1), nextOrderId(1)
{}

std::string ShopManager::getCurrentDate() const {
    std::time_t t = std::time(NULL);
    std::tm* tm_info = std::localtime(&t);
    std::ostringstream oss;
    oss << (1900 + tm_info->tm_year) << "-"
        << std::setw(2) << std::setfill('0') << (1 + tm_info->tm_mon) << "-"
        << std::setw(2) << std::setfill('0') << tm_info->tm_mday << " "
        << std::setw(2) << std::setfill('0') << tm_info->tm_hour << ":"
        << std::setw(2) << std::setfill('0') << tm_info->tm_min;
    return oss.str();
}

Customer* ShopManager::addCustomer(const std::string& name,
                                   const std::string& email,
                                   const std::string& phone,
                                   CustomerType type) {
    if (findCustomerByEmail(email))
        throw std::invalid_argument("Bu email bilan mijoz allaqachon ro'yxatdan o'tgan.");

    std::unique_ptr<Customer> c(new Customer(nextCustomerId++, name, email, phone, type));
    Customer* raw = c.get();
    customers.push_back(std::move(c));
    return raw;
}

Customer* ShopManager::findCustomer(int id) const {
    for (size_t i = 0; i < customers.size(); ++i)
        if (customers[i] && customers[i]->getId() == id)
            return customers[i].get();
    return NULL;
}

Customer* ShopManager::findCustomerByEmail(const std::string& email) const {
    for (size_t i = 0; i < customers.size(); ++i)
        if (customers[i] && customers[i]->getEmail() == email)
            return customers[i].get();
    return NULL;
}

bool ShopManager::removeCustomer(int id) {
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i] && customers[i]->getId() == id) {
            customers.erase(customers.begin() + (int)i);
            return true;
        }
    }
    return false;
}

Order* ShopManager::placeOrder(int customerId, int productId, int quantity) {
    Customer* customer = findCustomer(customerId);
    if (!customer) throw std::invalid_argument("Mijoz topilmadi.");
    Product* product = warehouse.findById(productId);
    if (!product) throw std::invalid_argument("Mahsulot topilmadi.");
    if (product->getQuantity() < quantity) throw std::runtime_error("Mahsulot kam.");

    std::unique_ptr<Order> order(new Order(nextOrderId++, customerId, customer->getDiscountRate(), getCurrentDate()));
    order->addItem(product, quantity);
    Order* raw = order.get();
    orders.push_back(std::move(order));
    return raw;
}

bool ShopManager::payOrder(int orderId) {
    Order* order = findOrder(orderId);
    if (!order || order->getStatus() != OrderStatus::PENDING) return false;
    Customer* customer = findCustomer(order->getCustomerId());
    if (!customer || !customer->canAfford(order->getTotal())) return false;
    
    for (const auto& item : order->getItems()) {
        if (!warehouse.removeStock(item.product->getId(), item.quantity)) return false;
    }
    customer->withdraw(order->getTotal());
    order->setStatus(OrderStatus::PROCESSING);
    return true;
}

bool ShopManager::updateOrderStatus(int orderId, OrderStatus status) {
    Order* order = findOrder(orderId);
    if (!order) return false;
    order->setStatus(status);
    return true;
}

Order* ShopManager::findOrder(int id) const {
    for (const auto& o : orders) if (o->getId() == id) return o.get();
    return NULL;
}

void ShopManager::searchProducts(const std::string& query) const {
    // GUI handles search now
}

void ShopManager::sortProducts(int choice) {
    if (choice == 1) warehouse.sortByPrice();
    else if (choice == 2) warehouse.sortByQuantity();
    else if (choice == 3) warehouse.sortByName();
}

void ShopManager::saveData() const {
    warehouse.saveToFile("products.txt");
    std::ofstream cOut("customers.txt");
    for (const auto& c : customers) cOut << c->serialize() << "\n";
    std::ofstream oOut("orders.txt");
    for (const auto& o : orders) oOut << o->serialize() << "\n";
}

void ShopManager::loadData() {
    warehouse.loadFromFile("products.txt");
    std::ifstream cIn("customers.txt");
    if (cIn.is_open()) {
        customers.clear();
        std::string line;
        int maxId = 0;
        while (std::getline(cIn, line)) {
            if (line.empty()) continue;
            auto p = split(line, '|');
            if (p.size() < 6) continue;
            int id = std::stoi(p[0]);
            if (id > maxId) maxId = id;
            customers.push_back(compat::make_unique<Customer>(id, p[1], p[2], p[3], (CustomerType)std::stoi(p[4]), std::stod(p[5])));
        }
        nextCustomerId = maxId + 1;
    }
}

void ShopManager::loadDemoData() {
    // Demo ma'lumotlar olib tashlandi
}

void ShopManager::printFullReport(std::ostream& os) const { warehouse.printReport(os); }
void ShopManager::printAllProducts(std::ostream& os) const { warehouse.printAll(os); }
void ShopManager::printAllCustomers(std::ostream& os) const { /* ... */ }
void ShopManager::printAllOrders(std::ostream& os) const { /* ... */ }
