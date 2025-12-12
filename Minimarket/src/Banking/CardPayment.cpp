//
// Created by ekatsune on 28.11.2025.
//
#include "../Exceptions/MinimarketException.hpp"
#include "CardPayment.hpp"
#include <iostream>
/**
 * @file CardPayment.cpp
 * @brief Реализация класса `CardPayment`.
 * @details
 * Этот файл содержит реализацию методов класса `CardPayment`,
 * который моделирует процессы проведения оплаты картой.
 * @author
 * Ekatsune
 */
bool CardPayment::ValidateCard() {
    Date today;
    if (expiry < today) {
        throw CardExpiredException(card_number);
    }
    return true;
}

bool CardPayment::Pay(const BYN& amount) {
    if (!ValidateCard()) {
        return false;
    }

    std::cout << "Оплата картой успешно проведена. ";
    amount.GetRubles();
    return true;
}

