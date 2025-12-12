#ifndef MINIMARKET_CART_HPP
#define MINIMARKET_CART_HPP

#include "../Products/Product.hpp"
#include <vector>

/**
 * @class Cart
 * @brief Класс корзины покупателя
 * Содержит список товаров, добавленных покупателем, и предоставляет методы для управления ими.
 */
class Cart {
private:
    std::vector<Product*> products_in_cart; /**< Список товаров в корзине */

public:
    /**
     * @brief Добавить товар в корзину
     * @param product Указатель на товар
     */
    void AddItem(Product* product);

    /**
     * @brief Удалить товар из корзины по имени
     * @param name Название товара
     */
    void RemoveItem(const std::string& name);

    /**
     * @brief Очистить корзину
     */
    void Clear();

    /**
     * @brief Получить все товары в корзине
     * @return const std::vector<Product*>& Список товаров
     */
    const std::vector<Product*>& GetItems() const;
};

#endif //MINIMARKET_CART_HPP
