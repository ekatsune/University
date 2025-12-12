#include "Beverage.hpp"
#include <iostream>
/**
 * @file Beverage.cpp
 * @brief Реализация класса `Beverage`.
 * @details
 * Этот файл содержит реализацию методов класса `Beverage`,
 * который моделирует безалкогольный напиток.
 * @author
 * Ekatsune
 */
Beverage::Beverage() : volume_liters(0.0), carbonated(false) {}

bool Beverage::IsCarbonated() const {
    return carbonated;
}

double Beverage::GetVolume() const {
    return volume_liters;
}
