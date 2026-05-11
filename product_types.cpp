#include "product_types.h"
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>

Electronics::Electronics(int id, const std::string& name, double price, int qty, const std::string& brand, int warranty)
    : Product(id, name, price, qty, Category::ELECTRONICS), brand(brand), warranty(warranty) {}

void Electronics::print(std::ostream& os) const {
    Product::print(os); os << " | Brend: " << brand << " | Kafolat: " << warranty;
}

std::string Electronics::serialize() const {
    std::ostringstream oss; oss << Product::serialize() << "|" << brand << "|" << warranty;
    return oss.str();
}

Clothing::Clothing(int id, const std::string& name, double price, int qty, const std::string& size, const std::string& color)
    : Product(id, name, price, qty, Category::CLOTHING), size(size), color(color) {}

void Clothing::print(std::ostream& os) const {
    Product::print(os); os << " | O'lcham: " << size << " | Rang: " << color;
}

std::string Clothing::serialize() const {
    std::ostringstream oss; oss << Product::serialize() << "|" << size << "|" << color;
    return oss.str();
}

Food::Food(int id, const std::string& name, double price, int qty, const std::string& expiry, bool organic)
    : Product(id, name, price, qty, Category::FOOD), expiry(expiry), organic(organic) {
    std::string n = name;
    for(auto &c : n) c = std::tolower(c);
    
    if (n.find("cola") != std::string::npos || n.find("suv") != std::string::npos || 
        n.find("fanta") != std::string::npos || n.find("sharb") != std::string::npos || 
        n.find("sut") != std::string::npos) {
        unit = "litr";
    } else if (n.find("kartosh") != std::string::npos || n.find("piyoz") != std::string::npos || 
               n.find("go'sht") != std::string::npos || n.find("guruch") != std::string::npos ||
               n.find("shakar") != std::string::npos || n.find("un") != std::string::npos) {
        unit = "kg";
    } else {
        unit = "dona";
    }
}

void Food::print(std::ostream& os) const {
    Product::print(os); os << " | Muddat: " << expiry << " | " << (organic ? "Organik" : "Oddiy");
}

std::string Food::serialize() const {
    std::ostringstream oss; oss << Product::serialize() << "|" << expiry << "|" << (organic ? 1 : 0);
    return oss.str();
}
