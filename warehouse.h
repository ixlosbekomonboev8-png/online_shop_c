#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "product.h"
#include "product_types.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>

class Warehouse {
    std::vector<std::unique_ptr<Product>> products;
    int nextId;

public:
    Warehouse();
    ~Warehouse() = default;

    void addProduct(std::unique_ptr<Product> product);
    Product* addElectronics(const std::string& name, double price, int qty, const std::string& brand, int warrantyMonths);
    Product* addClothing(const std::string& name, double price, int qty, const std::string& size, const std::string& color);
    Product* addFood(const std::string& name, double price, int qty, const std::string& expiryDate, bool isOrganic);

    Product* findById(int id) const;
    bool removeProduct(int id);
    bool addStock(int productId, int amount);
    bool removeStock(int productId, int amount);

    std::vector<Product*> getAllProducts() const;
    std::vector<Product*> getLowStockProducts() const;
    
    int    getTotalProductCount()   const;
    double getTotalInventoryValue() const;

    void printAll(std::ostream& os = std::cout) const;
    void printReport(std::ostream& os = std::cout) const;

    // Saralash
    void sortByPrice(bool ascending = true);
    void sortByQuantity(bool ascending = true);
    void sortByName(bool ascending = true);

    // Fayl
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    int getNextId() const { return nextId; }
};

#endif // WAREHOUSE_H
