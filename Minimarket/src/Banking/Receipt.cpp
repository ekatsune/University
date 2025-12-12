#include "../Exceptions/MinimarketException.hpp"
#include "Receipt.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
/**
 * @file Receipt.cpp
 * @brief Реализация класса `Receipt`.
 * @details
 * Этот файл содержит реализацию методов класса `Receipt`,
 * который моделирует чек покупателя.
 * @author
 * Ekatsune
 */
std::string Receipt::GetId() const {
    return std::to_string(receipt_ID);
}

BYN Receipt::GetTotal() const {
    return total;
}

void Receipt::AddItem(Product* product) {
    if (product) {
        items.push_back(product);
        total += product->GetPrice();
    }
}

void Receipt::DeleteItem(const std::string& name) {
    auto it = std::find_if(items.begin(), items.end(),
                           [&name](Product* current_product) -> bool {
                               return current_product != nullptr && current_product->GetName() == name;
                           });
    if (it != items.end()) {
        total = total - (*it)->GetPrice();
        items.erase(it);
    } else {
        throw ProductNotFoundException(name);
    }
}

int Receipt::CalculateTotals() {
    long long total_kopecks = 0;
    for (auto& item : items) {
        total_kopecks += item->GetPrice().GetRubles() * 100 + item->GetPrice().GetKopecks();
    }
    total = BYN(total_kopecks);
    return static_cast<int>(total.GetRubles());
}

void Receipt::Print() {
    std::cout << "Чек №" << receipt_ID << "\n";
    std::cout << "Дата: " << date;
    std::cout << "\n";
    std::cout << "Товары:\n";
    for (auto& item : items) {
        std::cout << "- " << item->GetName() << " : " << item->GetPrice().GetRubles() << " BYN\n";
    }
    std::cout << "Сумма: " << total.GetRubles() << " BYN\n";
    if (!payment_method_name.empty()) {
        std::cout << "Метод оплаты: " << payment_method_name << "\n";
    }
}

void Receipt::SaveToFile(std::string filename) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) return;

    file << "Чек №" << receipt_ID << "\n";
    file << "Дата: " << date;
    file << "\nТовары:\n";
    for (auto& item : items) {
        file << "- " << item->GetName() << " : " << item->GetPrice().GetRubles() << " BYN\n";
    }
    file << "Сумма: " << total.GetRubles() << " BYN\n";
    if (!payment_method_name.empty()) {
        file << "Метод оплаты: " << payment_method_name << "\n";
    }
    file << "--------------------------\n";

    file.close();
}

const Date& Receipt::GetDate() const { return date; }

const std::vector<Product*>& Receipt::GetItems() const { return items; }

void Receipt::SetTotal(const BYN& new_total) { total = new_total; }

void Receipt::AddDiscount(double percent) { discount_applied = percent; }

void Receipt::SubtractFromTotal(const BYN& value) { total -= value; }