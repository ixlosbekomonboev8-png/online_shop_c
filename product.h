#ifndef PRODUCT_H
#define PRODUCT_H

#include "shop_types.h"
#include <string>
#include <iostream>

class Product {
protected:
    int         id;
    std::string name;
    double      price;
    int         quantity;
    Category    category;
    std::string unit;

public:
    Product(int id, const std::string& name, double price, int quantity, Category category);
    virtual ~Product() = default;

    int         getId()       const { return id; }
    std::string getName()     const { return name; }
    double      getPrice()    const { return price; }
    int         getQuantity() const { return quantity; }
    std::string getUnit()     const { return unit; }
    
    void addStock(int amount);
    bool removeStock(int amount);
    bool isLowStock() const { return quantity <= LOW_STOCK_LIMIT; }

    virtual void print(std::ostream& os = std::cout) const;
    virtual std::string getTypeName() const { return "Mahsulot"; }
    virtual int         getTypeId()   const { return 0; }
    virtual std::string serialize()   const;
};

#endif // PRODUCT_H
