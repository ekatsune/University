#include "Shelf.hpp"
#include <algorithm>
/**
 * @file Shelf.cpp
 * @brief Реализация класса `Shelf`.
 * @details
 * Этот файл содержит реализацию методов класса `Shelf`,
 * который моделирует полку шкафа в минимаркете.
 * @author
 * Ekatsune
 */
void Shelf::AddProduct(Product* product) {
    if (product == nullptr) {
        std::cout << "Ошибка: попытка добавить nullptr в полку!\n";
        return;
    }
    products.push_back(product);
}

int Shelf::GetProductCount() const {
    return static_cast<int>(products.size());
}

const std::vector<Product*>& Shelf::GetAllProducts() const {
    return products;
}

Product* Shelf::FindByName(const std::string& name) {
    auto it = std::find_if(products.begin(), products.end(),
                           [&name](Product* product_on_shelf)  -> bool {
                               return product_on_shelf != nullptr && product_on_shelf ->GetName() == name;
                           });
    if (it != products.end())
        return *it;
    return nullptr;
}

Product* Shelf::RemoveProduct(const std::string& name) {
    auto it = std::find_if(products.begin(), products.end(),
                           [&](Product* p) {
                               return p->GetName() == name;
                           }
    );

    if (it == products.end())
        return nullptr;

    Product* removed = *it;
    products.erase(it);
    return removed;
}
