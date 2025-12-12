#include "WarehouseWorker.hpp"
#include "../Warehouse/Warehouse.hpp"
#include <fstream>
#include <iostream>
/**
 * @file WarehouseWorker.cpp
 * @brief Реализация класса `WarehouseWorker`.
 * @details
 * Этот файл содержит реализацию методов класса `WarehouseWorker`,
 * который моделирует работу сотрудника склада.
 * @author
 * Ekatsune
 */
void WarehouseWorker::AcceptTheProduct(std::string name,
Date data_of_manufacture, Date date_of_expiration,
BYN price, std::string information_about_the_manufacturer,
std::string storage_rules, std::string product_composition,
double unit_weight, int quantity) {
    Product product(
            name,
            data_of_manufacture,
            date_of_expiration,
            price,
            information_about_the_manufacturer,
            storage_rules,
            product_composition,
            unit_weight,
            quantity
    );
    work_place->AddProductToWarehouse(product);
    std::cout << "Товар добавлен на склад.\n";
    if (!work_place) {
        std::cout << "work_place is NULL!\n";
    }
}

void WarehouseWorker::ProductRegistration(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << "\n";
        return;
    }
    std::string name; Date data_of_manufacture;
    Date date_of_expiration; BYN price;
    std::string information_about_the_manufacturer;
    std::string storage_rules; std::string product_composition;
    std::string weight_str; std::string qty_str;
    //чтение
    std::getline(file, name); file >> data_of_manufacture;
    file >> date_of_expiration; file >> price; file.ignore();
    std::getline(file, information_about_the_manufacturer);
    std::getline(file, storage_rules);
    std::getline(file, product_composition);
    std::getline(file, weight_str);
    std::getline(file, qty_str);
    double unit_weight = 0.0;
    int quantity = 0;
    try {
        unit_weight = std::stod(weight_str);
        quantity = std::stoi(qty_str);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка преобразования чисел: " << e.what() << "\n";
        return;
    }
    file.close();
    AcceptTheProduct(name,data_of_manufacture, date_of_expiration, price, information_about_the_manufacturer,
                     storage_rules, product_composition, unit_weight, quantity);
}

void WarehouseWorker::WarehouseBalanceReport() const {
    const auto& products = work_place->GetProducts().GetAllProducts();

    if (products.empty()) {
        std::cout << "Склад пуст.\n";
        return;
    }

    std::cout << "=== Отчёт о остатках на складе ===\n\n";

    for (const auto& p : products) {
        std::cout << "Название: "     << p.GetName()     << "\n"
                  << "Кол-во: "        << p.GetQuantity() << "\n"
                  << "Цена: "          << p.GetPrice().GetRubles()    << "\n"
                  << "Дата произв.: "  << p.GetManufactureDate() << "\n"
                  << "Годен до: "      << p.GetExpirationDate()  << "\n"
                  << "Вес единицы: "   << p.GetWeight()   << " кг\n"
                  << "-----------------------------\n";
    }
}


void WarehouseWorker::ReplenishmentOfShelvesInMinimarket(Shelf& shelf,
                                                         const std::string& product_name,
                                                         int quantity) {
    auto& list = work_place->GetProducts().GetAllProducts();
    for (auto& p : list) {
        if (p.GetName() == product_name) {
            if (p.GetQuantity() < quantity) {
                std::cout << "Недостаточно товара на складе!\n";
                return;
            }
            p.SetQuantity(p.GetQuantity() - quantity);
            for (int i = 0; i < quantity; i++) {
                shelf.AddProduct(&p);
            }
            std::cout << "Полка пополнена товаром: "
                      << product_name << " x" << quantity << "\n"; return;
        }
    }
    std::cout << "Товар \"" << product_name << "\" отсутствует на складе.\n";
}

std::vector<Product> WarehouseWorker::GetWarehouseState() const {
    return work_place->GetProducts().GetAllProducts();
}
