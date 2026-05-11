#ifndef SHOP_MANAGER_H
#define SHOP_MANAGER_H

#include "shop_types.h"
#include "warehouse.h"
#include "customer.h"
#include "order.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class ShopManager {
    Warehouse                         warehouse;
    std::vector<std::unique_ptr<Customer>> customers;
    std::vector<std::unique_ptr<Order>>    orders;

    int nextCustomerId;
    int nextOrderId;

    std::string getCurrentDate() const;

public:
    ShopManager();
    ~ShopManager() = default;

    Warehouse& getWarehouse() { return warehouse; }

    Customer* addCustomer(const std::string& name,
                          const std::string& email,
                          const std::string& phone,
                          CustomerType type = CustomerType::REGULAR);
    Customer* findCustomer(int id)                  const;
    Customer* findCustomerByEmail(const std::string& email) const;
    bool      removeCustomer(int id);
    const std::vector<std::unique_ptr<Customer>>& getCustomers() const { return customers; }

    Order* placeOrder(int customerId, int productId, int quantity);
    bool addItemToOrder(int orderId, int productId, int quantity);
    bool payOrder(int orderId);
    bool updateOrderStatus(int orderId, OrderStatus status);

    Order* findOrder(int id)                         const;
    std::vector<Order*> getOrdersByCustomer(int customerId) const;
    const std::vector<std::unique_ptr<Order>>& getOrders() const { return orders; }

    void printAllProducts (std::ostream& os = std::cout) const;
    void printAllCustomers(std::ostream& os = std::cout) const;
    void printAllOrders   (std::ostream& os = std::cout) const;
    void printFullReport  (std::ostream& os = std::cout) const;

    // Qidiruv va Saralash
    void searchProducts(const std::string& query) const;
    void sortProducts(int choice);

    // Saqlash va Yuklash
    void saveData() const;
    void loadData();

    void loadDemoData();
};

#endif // SHOP_MANAGER_H
