//
// Created by ekatsune on 30.11.2025.
//

#ifndef MINIMARKET_PURCHASEORDER_HPP
#define MINIMARKET_PURCHASEORDER_HPP

#include <string>
#include <vector>
#include "../Products/Product.hpp"
class Provider;

/**
 * @class PurchaseOrder
 * @brief Класс заказа на поставку
 * Управляет списком продуктов, поставщиком, статусом заказа и расчётом стоимости.
 */
class PurchaseOrder {
public:
    /**
     * @brief Статус заказа
     */
    enum class Status {
        Draft,       /**< Черновик */
        Approved,    /**< Одобрен */
        Rejected,    /**< Отклонён */
        InDelivery,  /**< В пути */
        Delivered    /**< Доставлено */
    };

private:
    std::string order_id;                 /**< Уникальный идентификатор заказа */
    Date creation_date;                   /**< Дата создания заказа */
    BYN total_cost = 0;                   /**< Общая стоимость заказа */
    std::vector<Product> ordered_products; /**< Список продуктов в заказе */
    std::string destination_warehouse;    /**< Место назначения заказа */
    Provider* provider;                   /**< Поставщик */
    Status order_status = Status::Draft;  /**< Текущий статус заказа */

public:
    /** @brief Конструктор по умолчанию */
    PurchaseOrder()
            : provider(nullptr),
              ordered_products({}),
              destination_warehouse(""),
              order_status(Status::Draft),
              creation_date(Date())
    {}

    /**
     * @brief Конструктор с полными параметрами
     * @param provider Указатель на поставщика
     * @param products Список продуктов
     * @param destination Назначение доставки
     */
    PurchaseOrder(Provider* provider,
                  const std::vector<Product>& products,
                  const std::string& destination)
            : provider(provider),
              ordered_products(products),
              destination_warehouse(destination),
              creation_date(Date())
    {}

    /**
     * @brief Конструктор пустого заказа (для ошибок)
     * @param nullptr_t Игнорируется
     * @param products Список продуктов
     * @param destination Назначение доставки
     */
    PurchaseOrder(std::nullptr_t,
                  const std::vector<Product>& products,
                  const std::string& destination)
            : provider(nullptr),
              ordered_products(products),
              destination_warehouse(destination),
              order_status(Status::Rejected),
              creation_date(Date())
    {}

    /** @brief Получить поставщика заказа */
    Provider* GetSupplier() const;

    /** @brief Получить список продуктов */
    const std::vector<Product>& GetProducts() const;

    /** @brief Получить место назначения */
    const std::string& GetDestination() const;

    /**
     * @brief Преобразовать статус в строку
     * @param status Статус
     * @return std::string Строковое представление
     */
    std::string StatusToString(Status status) const;

    /** @brief Сгенерировать уникальный идентификатор заказа */
    void GenerateOrderID();

    /** @brief Добавить продукт в заказ */
    void AddProduct(const Product& product);

    /**
     * @brief Удалить продукт по имени
     * @param product_name Название продукта
     * @return true если продукт удалён, иначе false
     */
    bool RemoveProduct(const std::string& product_name);

    /** @brief Пересчитать общую стоимость заказа */
    void RecalculateTotal();

    /** @brief Установить место назначения заказа */
    void SetDestination(const std::string& warehouse);

    /** @brief Проверить, является ли заказ корректным */
    bool IsValid() const;

    /** @brief Установить статус заказа */
    void SetStatus(Status new_status);

    /** @brief Получить общий вес заказа */
    double GetTotalWeight() const;

    /** @brief Получить общую стоимость заказа */
    BYN GetTotalCost();
};

#endif //MINIMARKET_PURCHASEORDER_HPP
