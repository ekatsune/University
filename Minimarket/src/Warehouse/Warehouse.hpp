#pragma once
#include <iostream>
#include "ProductsInWarehouse.hpp"
#include "../Employee/WarehouseWorker.hpp"

/**
 * @class Warehouse
 * @brief Класс склада
 * Управляет списком продуктов на складе, статусом работы склада и операциями перемещения и сортировки.
 */
class Warehouse {
public:
    /** @brief Статус работы склада */
    enum warehouse_status {
        OPEN,                   /**< Склад открыт */
        CLOSE,                  /**< Склад закрыт */
        LUNCH_BREAK,            /**< Перерыв на обед */
        ACCEPTANCE_OF_PRODUCTS  /**< Приём товаров */
    };

private:
    int square;                                /**< Площадь склада */
    const std::string address;                 /**< Адрес склада */
    ProductsInWarehouse list_of_products_in_warehouse; /**< Продукты на складе */
    warehouse_status status;                   /**< Текущий статус работы склада */

public:
    /** @brief Конструктор по умолчанию */
    Warehouse() = default;

    /**
     * @brief Установить статус работы склада
     * @param new_status Новый статус
     */
    void SetStatus(warehouse_status new_status);

    /**
     * @brief Добавить продукт на склад
     * @param product Продукт для добавления
     */
    void AddProductToWarehouse(const Product& product);

    /**
     * @brief Получить объект списка продуктов на складе
     * @return ProductsInWarehouse& Список продуктов
     */
    ProductsInWarehouse& GetProducts();

    /**
     * @brief Найти продукт по названию
     * @param name Название продукта
     * @return Product* Указатель на продукт или nullptr, если не найден
     */
    Product* FindProductByName(const std::string& name);

    /**
     * @brief Переместить продукт в другой склад
     * @param target Целевой склад
     * @param name Название продукта
     * @param quantity Количество для перемещения (по умолчанию 1)
     * @return true если операция успешна, иначе false
     */
    bool MoveProductToOtherWarehouse(Warehouse& target, const std::string& name, int quantity = 1);

    /** @brief Сортировать продукты на складе по имени */
    void SortProductsByName();

    /** @brief Сортировать продукты на складе по дате окончания срока годности */
    void SortProductsByExpirationDate();
};
