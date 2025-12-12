#pragma once
#include "Product.hpp"

/**
 * @class Alcohol
 * @brief Класс алкогольного продукта
 * Наследует Product и добавляет информацию о проценте алкоголя и минимальном возрасте для покупки.
 * @see Product
 */
class Alcohol : public Product {
protected:
    double alcohol_percent; /**< Процент алкоголя в продукте */
    int legal_age;          /**< Минимальный возраст для покупки */

public:
    /**
     * @brief Проверка возможности покупки по возрасту
     * @param age Возраст покупателя
     * @return true если покупатель достиг допустимого возраста, иначе false
     */
    bool CanBuy(int age) const;
};
