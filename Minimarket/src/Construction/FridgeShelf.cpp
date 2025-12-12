#include "../Exceptions/MinimarketException.hpp"
#include "FridgeShelf.hpp"
/**
 * @file FridgeShelf.cpp
 * @brief Реализация класса `FridgeShelf`.
 * @details
 * Этот файл содержит реализацию методов класса `FridgeShelf`,
 * который моделирует холодильную полку.
 * @author
 * Ekatsune
 */
void FridgeShelf::AddProduct(Product* product) {
    if (!product) {
        throw NullProductException();
    }
    if (temperature > product->RequiresTemperature()) {
        throw MinimarketException(
                "Продукт \"" + product->GetName() + "\" не предназначен для хранения в холодильнике."
        );
    }
    products.push_back(product);
}

void FridgeShelf::SetTemperature(int new_temperature) {
    this->temperature = new_temperature;
}