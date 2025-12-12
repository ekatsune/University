#ifndef MINIMARKET_PROVIDER_HPP
#define MINIMARKET_PROVIDER_HPP

#include <string>
#include <vector>
#include "PurchaseOrder.hpp"
#include "ProductsDelivery.hpp"

/**
 * @class PurchaseOrder
 * @brief Класс поставщика
 * Управляет информацией о компании-поставщике, заказами, доставкой и рейтингом надёжности.
 */
class Provider {
private:
    std::string company_name;                 /**< Название компании */
    std::string contact_phone;                /**< Контактный телефон */
    std::string contact_email;                /**< Контактный email */
    double reliability_rating;                /**< Рейтинг надёжности поставщика */
    std::vector<std::string> product_categories; /**< Категории продуктов, которые поставляет */
    bool is_busy;                             /**< Статус занятости поставщика */
    std::vector<ProductsDelivery> supplies;   /**< История поставок */
    size_t orders_completed;                  /**< Количество успешно выполненных заказов */
    size_t orders_failed;                     /**< Количество неудачных заказов */

public:
    /**
     * @brief Конструктор поставщика
     * @param name Название компании
     * @param phone Контактный телефон
     * @param email Контактный email
     */
    Provider(const std::string& name,
             const std::string& phone,
             const std::string& email)
            : company_name(name), contact_phone(phone), contact_email(email),
              is_busy(false),
              orders_completed(0),
              orders_failed(0) {}

    /**
     * @brief Создать заказ на продукты
     * @param products Список продуктов для заказа
     * @param destination Место доставки
     * @return PurchaseOrder Заказ
     */
    PurchaseOrder CreateOrder(const std::vector<Product>& products,
                              const std::string& destination) const;

    /** @brief Получить название компании */
    const std::string& GetName() const;

    /** @brief Получить контактный телефон */
    const std::string& GetPhone() const;

    /** @brief Получить контактный email */
    const std::string& GetEmail() const;

    /** @brief Проверка доступности поставщика */
    bool IsAvailable() const;

    /**
     * @brief Запустить доставку заказа
     * @param order Заказ для доставки
     * @return ProductsDelivery Объект поставки
     */
    ProductsDelivery StartDelivery(PurchaseOrder& order);

    /** @brief Рассчитать надёжность поставщика */
    double CalculateReliability() const;

    /**
     * @brief Добавить категорию продуктов, которую поставляет поставщик
     * @param category Название категории
     */
    void AddProductCategory(const std::string& category);

    /**
     * @brief Отследить поставку по её ID
     * @param supply_id Индекс поставки
     * @return const ProductsDelivery* Указатель на поставку или nullptr, если не найдено
     */
    const ProductsDelivery* TrackSupply(size_t supply_id) const;

    /**
     * @brief Завершить заказ и обновить статистику
     * @param success true если заказ выполнен успешно, иначе false
     */
    void FinishOrder(bool success);
};

#endif //MINIMARKET_PROVIDER_HPP
