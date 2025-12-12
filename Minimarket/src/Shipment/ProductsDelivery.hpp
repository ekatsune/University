#ifndef MINIMARKET_PRODUCTSDELIVERY_HPP
#define MINIMARKET_PRODUCTSDELIVERY_HPP

#include <vector>
#include <string>
#include "../Warehouse/ProductsInWarehouse.hpp"
#include "../Products/Product.hpp"
#include "DeliveryTransport.hpp"

class Provider;       /**< Forward declaration поставщика */
class PurchaseOrder;  /**< Forward declaration заказа */

/**
 * @class ProductsDelivery
 * @brief Класс поставки товаров
 * Управляет доставкой товаров от поставщика к складу с использованием транспорта.
 */
class ProductsDelivery {
private:
    PurchaseOrder* order = nullptr; /**< Заказ, который доставляется */
    DeliveryTransport transport;     /**< Транспорт для доставки */
    bool delivered = false;          /**< Статус доставки */

public:
    /** @brief Конструктор по умолчанию */
    ProductsDelivery()
            : order(nullptr),
              transport("N/A", "N/A", 0),
              delivered(false)
    { }

    /**
     * @brief Конструктор пустой доставки (ошибочный заказ)
     * @param nullptr_t Игнорируется
     * @param products Список продуктов (не используется)
     * @param info Строка информации (не используется)
     */
    ProductsDelivery(std::nullptr_t,
                     const std::vector<Product>&,
                     const std::string&)
            : order(nullptr),
              transport("N/A", "N/A", 0),
              delivered(false)
    { }

    /**
     * @brief Конструктор с указанием заказа и транспорта
     * @param order Заказ для доставки
     * @param transport Транспорт для доставки
     */
    ProductsDelivery(PurchaseOrder& order,
                     const DeliveryTransport& transport)
            : order(&order),
              transport(transport),
              delivered(false)
    { }

    /**
     * @brief Пометить доставку как выполненную и добавить товары на склад
     * @param warehouse_products Склад, куда доставляются товары
     */
    void MarkDelivered(ProductsInWarehouse& warehouse_products);

    /**
     * @brief Получить заказ, связанный с доставкой
     * @return PurchaseOrder* Указатель на заказ
     */
    PurchaseOrder* GetOrder() const;

    /**
     * @brief Получить транспорт, используемый для доставки
     * @return const DeliveryTransport& Ссылка на транспорт
     */
    const DeliveryTransport& GetTransport() const;

    /**
     * @brief Проверка, была ли доставка выполнена
     * @return true если доставка завершена, иначе false
     */
    bool IsDelivered() const;
};

#endif //MINIMARKET_PRODUCTSDELIVERY_HPP
