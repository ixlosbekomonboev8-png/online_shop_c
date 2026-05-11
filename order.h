#ifndef ORDER_H
#define ORDER_H

#include "shop_types.h"
#include "product.h"
#include <vector>
#include <string>
#include <iostream>

struct OrderItem {
    Product*    product;
    int         quantity;
    double      unitPrice;
    OrderItem(Product* p, int qty, double price) : product(p), quantity(qty), unitPrice(price) {}
    double subtotal() const { return unitPrice * quantity; }
};

class Order {
    int                   id;
    int                   customerId;
    std::vector<OrderItem> items;
    OrderStatus           status;
    double                discountRate;
    std::string           createdAt;

public:
    Order(int id, int customerId, double discountRate, const std::string& createdAt);
    int         getId()          const { return id; }
    int         getCustomerId()  const { return customerId; }
    OrderStatus getStatus()      const { return status; }
    std::string getCreatedAt()   const { return createdAt; }
    double      getTotal()       const;
    void        addItem(Product* product, int quantity);
    void        setStatus(OrderStatus s) { status = s; }
    const std::vector<OrderItem>& getItems() const { return items; }

    void print(std::ostream& os = std::cout) const;
    std::string serialize() const;
};

#endif // ORDER_H
