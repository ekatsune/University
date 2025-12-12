#include "PaymentMethod.hpp"
/**
 * @file PaymentMethod.cpp
 * @brief Реализация класса `PaymentMethod`.
 * @details
 * Этот файл содержит реализацию методов класса `PaymentMethod`,
 * который является базовым классом для различных способов оплаты.
 * @author
 * Ekatsune
 */
std::string PaymentMethod::GetName() const  {
    return name;
}

bool PaymentMethod::IsCash() const {
    return false;
}