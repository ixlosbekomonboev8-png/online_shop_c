#ifndef SHOP_TYPES_H
#define SHOP_TYPES_H

#include <string>
#include <vector>
#include <sstream>
#include <memory>

const double TAX_RATE         = 0.12;
const double DISCOUNT_VIP     = 0.15;
const double DISCOUNT_REGULAR = 0.05;
const int    LOW_STOCK_LIMIT  = 5;

enum class Category { ELECTRONICS, CLOTHING, FOOD, FURNITURE, BOOKS, OTHER };
enum class OrderStatus { PENDING, PROCESSING, SHIPPED, DELIVERED, CANCELLED };
enum class CustomerType { REGULAR, VIP };

inline std::string categoryToString(Category cat) { (void)cat; return "Mahsulot"; }
inline std::string customerTypeToString(CustomerType t) { return (t == CustomerType::VIP) ? "VIP" : "Oddiy"; }

inline std::string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING:    return "Kutilmoqda";
        case OrderStatus::PROCESSING: return "Jarayonda";
        case OrderStatus::SHIPPED:    return "Yuborilgan";
        case OrderStatus::DELIVERED:  return "Yetkazilgan";
        case OrderStatus::CANCELLED:  return "Bekor qilingan";
        default: return "Noma'lum";
    }
}

inline std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) tokens.push_back(token);
    return tokens;
}

namespace compat {
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif // SHOP_TYPES_H
