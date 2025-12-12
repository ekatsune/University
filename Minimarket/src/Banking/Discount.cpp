#include "Discount.hpp"
/**
 * @file Discount.cpp
 * @brief Реализация класса `Discount`.
 * @details
 * Этот файл содержит реализацию методов класса `Discount`,
 * который моделирует скидку с указанием процента, даты действия и имени.
 * @author
 * Ekatsune
 */
bool Discount::IsActive(const Date& today) const {
    // скидка активна, если today находится в диапазоне [start_date, end_date]
    return !(today < start_date) && !(end_date < today);
}

double Discount::GetPercent() const { return percent; }

const std::string& Discount::GetName() const { return name; }