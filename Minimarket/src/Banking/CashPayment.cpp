#include "../Exceptions/MinimarketException.hpp"
#include "CashPayment.hpp"
/**
 * @file CashPayment.cpp
 * @brief Реализация класса `CashPayment`.
 * @details
 * Этот файл содержит реализацию методов класса `CashPayment`,
 * который моделирует процессы при оплате наличными.
 * @author
 * Ekatsune
 */
void CashPayment::SetChange(BYN current_change) {
    change = current_change;
}
// Оплата наличными
bool CashPayment::Pay(const BYN& amount) {
    if (cash_given < amount) {
        throw NotEnoughCashException(cash_given.GetRubles(),amount.GetRubles());
    }
    BYN current_change = cash_given - amount;
    SetChange(current_change);
    return true;
}

// Получить сдачу
BYN CashPayment::GetChange() const {
    return change;
}

// Получить сколько дал покупатель
BYN CashPayment::GetGiven() {
    return cash_given;
}

// Проверка наличной оплаты
bool CashPayment::IsCash() const {
    return true; // Это именно наличная оплата
}