#include "warehouse.h"
#include <algorithm>
#include <iomanip>
#include <fstream>

Warehouse::Warehouse() : nextId(1) {}

void Warehouse::addProduct(std::unique_ptr<Product> product) {
    products.push_back(std::move(product));
}

Product* Warehouse::addElectronics(const std::string& name, double price, int qty, const std::string& brand, int warrantyMonths) {
    auto p = compat::make_unique<Electronics>(nextId++, name, price, qty, brand, warrantyMonths);
    Product* ptr = p.get();
    products.push_back(std::move(p));
    return ptr;
}

Product* Warehouse::addClothing(const std::string& name, double price, int qty, const std::string& size, const std::string& color) {
    auto p = compat::make_unique<Clothing>(nextId++, name, price, qty, size, color);
    Product* ptr = p.get();
    products.push_back(std::move(p));
    return ptr;
}

Product* Warehouse::addFood(const std::string& name, double price, int qty, const std::string& expiryDate, bool isOrganic) {
    auto p = compat::make_unique<Food>(nextId++, name, price, qty, expiryDate, isOrganic);
    Product* ptr = p.get();
    products.push_back(std::move(p));
    return ptr;
}

Product* Warehouse::findById(int id) const {
    for (const auto& p : products) if (p->getId() == id) return p.get();
    return NULL;
}

bool Warehouse::removeProduct(int id) {
    for (auto it = products.begin(); it != products.end(); ++it) {
        if ((*it)->getId() == id) {
            products.erase(it);
            return true;
        }
    }
    return false;
}

bool Warehouse::addStock(int productId, int amount) {
    Product* p = findById(productId);
    if (!p) return false;
    p->addStock(amount);
    return true;
}

bool Warehouse::removeStock(int productId, int amount) {
    Product* p = findById(productId);
    if (!p) return false;
    return p->removeStock(amount);
}

std::vector<Product*> Warehouse::getAllProducts() const {
    std::vector<Product*> res;
    for (const auto& p : products) res.push_back(p.get());
    return res;
}

std::vector<Product*> Warehouse::getLowStockProducts() const {
    std::vector<Product*> res;
    for (const auto& p : products) if (p->isLowStock()) res.push_back(p.get());
    return res;
}

int Warehouse::getTotalProductCount() const { return products.size(); }

double Warehouse::getTotalInventoryValue() const {
    double total = 0;
    for (const auto& p : products) total += p->getPrice() * p->getQuantity();
    return total;
}

void Warehouse::sortByPrice(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const std::unique_ptr<Product>& a, const std::unique_ptr<Product>& b) {
        return ascending ? (a->getPrice() < b->getPrice()) : (a->getPrice() > b->getPrice());
    });
}

void Warehouse::sortByQuantity(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const std::unique_ptr<Product>& a, const std::unique_ptr<Product>& b) {
        return ascending ? (a->getQuantity() < b->getQuantity()) : (a->getQuantity() > b->getQuantity());
    });
}

void Warehouse::sortByName(bool ascending) {
    std::sort(products.begin(), products.end(), [ascending](const std::unique_ptr<Product>& a, const std::unique_ptr<Product>& b) {
        return ascending ? (a->getName() < b->getName()) : (a->getName() > b->getName());
    });
}

void Warehouse::saveToFile(const std::string& filename) const {
    std::ofstream fout(filename);
    for (const auto& p : products) fout << p->serialize() << "\n";
}

void Warehouse::loadFromFile(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) return;
    products.clear();
    std::string line;
    int maxId = 0;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        auto p = split(line, '|');
        if (p.size() < 5) continue;
        int type = std::stoi(p[0]);
        int id = std::stoi(p[1]);
        if (id > maxId) maxId = id;
        if (type == 1) products.push_back(compat::make_unique<Electronics>(id, p[2], std::stod(p[3]), std::stoi(p[4]), p[5], std::stoi(p[6])));
        else if (type == 2) products.push_back(compat::make_unique<Clothing>(id, p[2], std::stod(p[3]), std::stoi(p[4]), p[5], p[6]));
        else if (type == 3) products.push_back(compat::make_unique<Food>(id, p[2], std::stod(p[3]), std::stoi(p[4]), p[5], std::stoi(p[6]) == 1));
    }
    nextId = maxId + 1;
}

void Warehouse::printAll(std::ostream& os) const { for (const auto& p : products) p->print(os); }
void Warehouse::printReport(std::ostream& os) const { os << "Jami mahsulot: " << products.size() << "\n"; }
