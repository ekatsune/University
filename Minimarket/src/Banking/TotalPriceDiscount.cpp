#include "TotalPriceDiscount.hpp"
#include <iostream>
#include <cmath>
/**
 * @file TotalPriceDiscount.cpp
 * @brief Реализация класса `TotalPriceDiscount`.
 * @details
 * Этот файл содержит реализацию методов класса `TotalPriceDiscount`,
 * который моделирует скидку на определённую набранную сумму в чеке.
 * @author
 * Ekatsune
 */
void TotalPriceDiscount::Apply(Receipt& receipt) const {
    if (!IsActive(receipt.GetDate())) {
        std::cout << "Скидка \"" << name << "\" не активна на эту дату.\n";
        return;
    }
    BYN total = receipt.GetTotal();
    if (total < threshold) {
        std::cout << "Скидка \"" << name << "\" не применена. "
                  << "Сумма " << total << " меньше порога " << threshold.GetRubles() << " BYN" ".\n";
        return;
    }
    BYN discount_value = total * (percent / 100.0);
    receipt.AddDiscount(percent);
    receipt.SubtractFromTotal(discount_value);
    std::cout << "Применена скидка \"" << name
              << "\" (" << percent << "%). Скидка составила: "
              << discount_value << "\n";
}
