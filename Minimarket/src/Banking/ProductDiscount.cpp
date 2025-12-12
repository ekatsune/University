#include "ProductDiscount.hpp"
#include <iostream>
#include <cmath>
/**
 * @file ProductDiscount.cpp
 * @brief Реализация класса `ProductDiscount`.
 * @details
 * Этот файл содержит реализацию метода класса `ProductDiscount`.
 * @author
 * Ekatsune
 */
void ProductDiscount::Apply(Receipt& receipt) const {
    if (!IsActive(receipt.GetDate())) {
        std::cout << "Скидка \"" << name << "\" не активна на эту дату.\n";
        return;
    }
    const auto& items = receipt.GetItems();
    long long discount_kopecks = 0;bool found = false;
    for (auto* p : items) {
        if (p->GetName() == product_name) {
            found = true; long long price_kopecks =
                    p->GetPrice().GetRubles() * 100 + p->GetPrice().GetKopecks();
            discount_kopecks += static_cast<long long>(
                    std::round(static_cast<double>(price_kopecks) * percent / 100.0)
            );
        }
    }
    if (!found) {
        std::cout << "Скидка \"" << name << "\" не применена: "
                  << "товар \"" << product_name << "\" отсутствует в чеке.\n";
        return;
    }
    receipt.SubtractFromTotal(BYN(discount_kopecks));
    receipt.AddDiscount(percent);
    std::cout << "Применена скидка \"" << name << "\" (" << percent
              << "% на товар \"" << product_name << "\").\n"
              << "Размер скидки: " << BYN(discount_kopecks) << "\n";
}



