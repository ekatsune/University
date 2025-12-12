#include "Product.hpp"  // или соответствующий заголовочный файл
#include <iostream>
/**
 * @file Product.cpp
 * @brief Реализация класса `Product`.
 * @details
 * Этот файл содержит реализацию методов класса `Product`,
 * который моделирует базовый продукт с информацией о нём.
 * @author
 * Ekatsune
 */
const std::string& Product::GetName() const {
    return name;
}

BYN Product::GetPrice() const {
    return price;
}

std::string Product::GetInformationAboutTheManufacturer() const {
    return information_about_the_manufacturer;
}

void Product::GoBad() {
    date_of_expiration = data_of_manufacture;
    std::cout << "Product '" << name << "' has gone bad.\n";
}

std::string Product::GetStorageRules() {
    return storage_rules;
}

std::string Product::GetProductComposition() {
    return product_composition;
}

int Product::RequiresTemperature() {
    return 18;
}

void Product::SetQuantity(int cur_quantity) { quantity = cur_quantity; }

void Product::DecreaseQuantity(int cur_quantity) {
    if (cur_quantity > quantity) quantity = 0;
    else quantity -= cur_quantity;
}

double Product::GetWeight() const{
    return unit_weight*quantity;
}

int Product::GetQuantity() const {
    return quantity;
}

const Date &Product::GetManufactureDate() const {
    return data_of_manufacture;
}

const Date &Product::GetExpirationDate() const {
    return date_of_expiration;
}