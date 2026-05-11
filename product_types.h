#ifndef PRODUCT_TYPES_H
#define PRODUCT_TYPES_H

#include "product.h"

class Electronics : public Product {
    std::string brand;
    int         warranty;
public:
    Electronics(int id, const std::string& name, double price, int qty, const std::string& brand, int warranty);
    void print(std::ostream& os = std::cout) const override;
    std::string getTypeName() const override { return "Elektronika"; }
    int         getTypeId()   const override { return 1; }
    std::string serialize()   const override;
};

class Clothing : public Product {
    std::string size;
    std::string color;
public:
    Clothing(int id, const std::string& name, double price, int qty, const std::string& size, const std::string& color);
    void print(std::ostream& os = std::cout) const override;
    std::string getTypeName() const override { return "Kiyim"; }
    int         getTypeId()   const override { return 2; }
    std::string serialize()   const override;
};

class Food : public Product {
    std::string expiry;
    bool        organic;
public:
    Food(int id, const std::string& name, double price, int qty, const std::string& expiry, bool organic);
    void print(std::ostream& os = std::cout) const override;
    std::string getTypeName() const override { return "Oziq-ovqat"; }
    int         getTypeId()   const override { return 3; }
    std::string serialize()   const override;
};

#endif // PRODUCT_TYPES_H
