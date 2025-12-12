#pragma once
#include "Product.hpp"

/**
 * @class Beverage
 * @brief Класс напитка
 * Наследует Product и добавляет информацию о объёме и газированности.
 * @see Product
 */
class Beverage : public Product {
protected:
    double volume_liters; /**< Объём напитка в литрах */
    bool carbonated;      /**< Флаг газированного напитка */

public:
    /** @brief Конструктор по умолчанию */
    Beverage();

    /**
     * @brief Проверка, газированный ли напиток
     * @return true если напиток газированный, иначе false
     */
    bool IsCarbonated() const;

    /**
     * @brief Получить объём напитка
     * @return double Объём в литрах
     */
    double GetVolume() const;
};
