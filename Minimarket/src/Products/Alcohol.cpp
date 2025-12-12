#include "Alcohol.hpp"
#include <iostream>
/**
 * @file Alcohol.cpp
 * @brief Реализация класса `Alcohol`.
 * @details
 * Этот файл содержит реализацию методов класса `Alcohol`,
 * который моделирует алкогольный напиток.
 * @author
 * Ekatsune
 */
bool Alcohol::CanBuy(int age) const {
    return age >= legal_age;
}