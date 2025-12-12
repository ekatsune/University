#include "../Exceptions/MinimarketException.hpp"
#include "CashRegister.hpp"
#include "Receipt.hpp"
#include <iostream>
/**
 * @file CashRegister.cpp
 * @brief Реализация класса `CashRegister`.
 * @details
 * Этот файл содержит реализацию методов класса `CashRegister`,
 * который моделирует процессы работы кассового аппарата.
 * @author
 * Ekatsune
 */
void CashRegister::OpenShift(std::string id) {
    if (is_open) throw ShiftAlreadyOpenException();
    cashier_id = id;
    is_open = true;
    cash_inside = BYN(0, 0);
    receipts.clear();

    std::cout << "Смена открыта. Кассир ID: " << cashier_id << "\n";
}

void CashRegister::CloseShift() {
    if (!is_open) throw ShiftNotOpenException();
    std::cout << "Смена закрыта. Всего денег в кассе: "
              << cash_inside.GetRubles() << "." << cash_inside.GetKopecks()
              << " BYN\n";

    is_open = false;
}

Receipt CashRegister::CreateReceipt(const Cart& cart) {
    if (!is_open) throw CashRegisterClosedException();

    const auto& items = cart.GetItems();
    if (items.empty()) throw EmptyCartException();

    for (Product* p : items) {
        if (!p) throw NullProductException();
    }

    Receipt receipt;
    for (Product* p : items) {
        receipt.AddItem(p);
    }

    receipts.push_back(receipt);
    return receipt;
}

const std::vector<Receipt>& CashRegister::GetReceipts() const {
    return receipts;
}

BYN CashRegister::GetTotalCash() const {
    return cash_inside;
}

void CashRegister::AddCash(const BYN& amount) {
    if (!is_open) throw CashRegisterClosedException();
    cash_inside = cash_inside + amount;
}

bool CashRegister::HasEnoughCash(const BYN& amount) const {
    return !(cash_inside < amount);
}

bool CashRegister::IsShiftOpen() {return is_open;}
