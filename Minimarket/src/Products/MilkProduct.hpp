#pragma once
#include "Product.hpp"

/**
 * @class MilkProduct
 * @brief Класс молочного продукта
 * Наследует Product и добавляет информацию о температуре хранения и сроке хранения после открытия.
 * @see Product
 */
class MilkProduct : public Product {
protected:
    int storage_temperature;          /**< Температура хранения продукта */
    Date shelf_life_after_opening;    /**< Срок хранения после открытия упаковки */

public:
    /**
     * @brief Конструктор молочного продукта
     * @param name Название продукта
     * @param dom Дата производства
     * @param doe Дата окончания срока годности
     * @param price Цена продукта
     * @param disc Процент скидки
     * @param manuf Производитель
     * @param rules Правила хранения
     * @param comp Состав продукта
     * @param weight Вес одной единицы
     * @param temp Температура хранения
     * @param shelf Срок хранения после открытия
     */
    MilkProduct(const std::string& name, const Date& dom, const Date& doe, const BYN& price,
                double disc, const std::string& manuf, const std::string& rules,
                const std::string& comp, double weight,
                int temp, Date shelf)
            : Product(name, dom, doe, price, disc, manuf, rules, comp, weight),
              storage_temperature(temp), shelf_life_after_opening(shelf) {};

    /**
     * @brief Получить требуемую температуру хранения продукта
     * @return int Температура в градусах
     */
    int RequiresTemperature() override;
};
