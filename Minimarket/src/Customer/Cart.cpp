#include "../Exceptions/MinimarketException.hpp"
#include "Cart.hpp"
#include <algorithm>
#include <stdexcept>
/**
 * @file Cart.cpp
 * @brief Реализация класса `Cart`.
 * @details
 * Этот файл содержит реализацию методов класса `Cart`,
 * который моделирует корзину для покупок.
 * @author
 * Ekatsune
 */
void Cart::AddItem(Product* current_product) {
    if (current_product != nullptr) {
        products_in_cart.push_back(current_product);
    }
}

void Cart::RemoveItem(const std::string& name) {
    auto it = std::find_if(products_in_cart.begin(), products_in_cart.end(),
                           [&name](Product* current_product) -> bool {
                               return current_product != nullptr && current_product->GetName() == name;
                           });
    if (it != products_in_cart.end()) {
        products_in_cart.erase(it);
    } else {
        throw ProductNotFoundException(name);
    }
}

void Cart::Clear() {
    products_in_cart.clear();
}

const std::vector<Product*>& Cart::GetItems() const {
    return products_in_cart;
}