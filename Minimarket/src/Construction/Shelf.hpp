#ifndef MINIMARKET_SHELF_HPP
#define MINIMARKET_SHELF_HPP

#include "../Products/Product.hpp"
#include <vector>

/**
 * @class Shelf
 * @brief Класс полки.
 * Представляет полку в магазине, на которой хранятся продукты.
 */
class Shelf {
protected:
    std::vector<Product*> products; /**< Список продуктов на полке */

public:
    /** @brief Виртуальный деструктор */
    virtual ~Shelf() = default;

    /**
     * @brief Добавить продукт на полку
     * @param current_product Указатель на продукт
     */
    virtual void AddProduct(Product* current_product);

    /**
     * @brief Получить количество продуктов на полке
     * @return int Количество продуктов
     */
    int GetProductCount() const;

    /**
     * @brief Получить все продукты на полке
     * @return const std::vector<Product*>& Список продуктов
     */
    const std::vector<Product*>& GetAllProducts() const;

    /**
     * @brief Найти продукт по имени
     * @param name Название продукта
     * @return Product* Указатель на продукт, или nullptr если не найден
     */
    Product* FindByName(const std::string& name);

    /**
     * @brief Удалить продукт по имени
     * @param name Название продукта
     * @return Product* Указатель на удалённый продукт, или nullptr если не найден
     */
    Product* RemoveProduct(const std::string& name);
};

#endif //MINIMARKET_SHELF_HPP
