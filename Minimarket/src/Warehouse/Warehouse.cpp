#include <algorithm>
#include "Warehouse.hpp"
/**
 * @file Warehouse.cpp
 * @brief Реализация класса `Warehouse`.
 * @details
 * Этот файл содержит реализацию методов класса `Warehouse`,
 * который моделирует работу на складе.
 * @author
 * Ekatsune
 */
void Warehouse::AddProductToWarehouse(const Product &product)  {
    list_of_products_in_warehouse.AddProductToListOfProd(product);
}

ProductsInWarehouse& Warehouse::GetProducts() {
    return list_of_products_in_warehouse;
}

void Warehouse::SetStatus(WarehouseStatus new_status) {
    status = new_status;
}

Product* Warehouse::FindProductByName(const std::string& name) {
    return list_of_products_in_warehouse.FindByName(name);
}

bool Warehouse::MoveProductToOtherWarehouse(Warehouse& target, const std::string& name, int quantity) {
    Product* p = FindProductByName(name);
    if (!p || p->GetQuantity() < quantity) return false;

    Product copy = *p;
    copy.SetQuantity(quantity);

    target.AddProductToWarehouse(copy);

    p->DecreaseQuantity(quantity);
    return true;
}

void Warehouse::SortProductsByName() {
    auto& products = list_of_products_in_warehouse.GetAllProducts();
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) {
                  return a.GetName() < b.GetName();
              });
}

void Warehouse::SortProductsByExpirationDate() {
    auto& products = list_of_products_in_warehouse.GetAllProducts();
    std::sort(products.begin(), products.end(),
              [](const Product& a, const Product& b) {
                  return a.GetExpirationDate() < b.GetExpirationDate();
              });
}
