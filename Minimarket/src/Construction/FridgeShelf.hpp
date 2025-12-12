#ifndef MINIMARKET_FRIDGESHELF_HPP
#define MINIMARKET_FRIDGESHELF_HPP

#include "Shelf.hpp"

/**
 * @class FridgeShelf
 * @brief Класс холодильной полки
 * Наследует Shelf и хранит продукты при заданной температуре.
 * @see Shelf
 */
class FridgeShelf : public Shelf {
private:
    int temperature = 5; /**< Температура хранения продуктов (°C) */

public:
    /**
     * @brief Добавить продукт на полку
     *
     * Переопределяет метод Shelf::AddProduct.
     * @param product Указатель на продукт
     */
    void AddProduct(Product* product) override;

    /**
     * @brief Установить температуру хранения
     * @param new_temperature Новая температура в °C
     */
    void SetTemperature(int new_temperature);
};

#endif //MINIMARKET_FRIDGESHELF_HPP
