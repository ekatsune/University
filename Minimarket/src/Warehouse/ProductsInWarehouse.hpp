#pragma once
#include "../Products/Product.hpp"
#include <iostream>
#include <vector>

/**
 * @class ProductsInWarehouse
 * @brief Класс для управления продуктами на складе
 * Хранит список продуктов и предоставляет методы для добавления, удаления и поиска.
 */
class ProductsInWarehouse {
private:
    std::vector<Product> list_of_products_in_warehouse; /**< Список продуктов на складе */

public:
    /**
     * @brief Добавить продукт на склад
     * @param product Продукт для добавления
     */
    void AddProductToListOfProd(const Product& product);

    /** @brief Удалить продукт со склада (удаляет последний добавленный) */
    void DeleteProductToListOfProd();

    /**
     * @brief Получить все продукты на складе (константная версия)
     * @return const std::vector<Product>& Список всех продуктов
     */
    const std::vector<Product>& GetAllProducts() const;

    /**
     * @brief Получить все продукты на складе (не константная версия)
     * @return std::vector<Product>& Список всех продуктов
     */
    std::vector<Product>& GetAllProducts();

    /**
     * @brief Найти продукт по названию
     * @param name Название продукта
     * @return Product* Указатель на продукт или nullptr, если не найден
     */
    Product* FindByName(const std::string& name);
};
