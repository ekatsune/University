#include "ProductsInWarehouse.hpp"
#include <algorithm>
/**
 * @file ProductsInWarehouse.cpp
 * @brief Реализация класса `ProductsInWarehouse`.
 * @details
 * Этот файл содержит реализацию методов класса `ProductsInWarehouse`,
 * который моделирует базу данных для продуктов на складе.
 * @author
 * Ekatsune
 */
void ProductsInWarehouse::DeleteProductToListOfProd() {
    std::cout << "Введите название товара для удаления: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);
    auto old_size = list_of_products_in_warehouse.size();

    list_of_products_in_warehouse.erase(
            std::remove_if(
                    list_of_products_in_warehouse.begin(),
                    list_of_products_in_warehouse.end(),
                    [&](const Product& p) { return p.GetName() == name; }
            ),
            list_of_products_in_warehouse.end()
    );

    if (list_of_products_in_warehouse.size() < old_size)
        std::cout << "Удалено товаров: " << (old_size - list_of_products_in_warehouse.size()) << "\n";
    else
        std::cout << "Товар не найден.\n";
}

const std::vector<Product>& ProductsInWarehouse::GetAllProducts() const {
    return list_of_products_in_warehouse;
}
std::vector<Product>& ProductsInWarehouse::GetAllProducts() {
    return list_of_products_in_warehouse;
}
Product* ProductsInWarehouse::FindByName(const std::string& name) {
    for (auto& p : list_of_products_in_warehouse) {
        if (p.GetName() == name) return &p;
    }
    return nullptr;
}

void ProductsInWarehouse::AddProductToListOfProd(const Product& product) {
    list_of_products_in_warehouse.emplace_back(product);
    std::cout << "Товар добавлен на склад.\n";
}

