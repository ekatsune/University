#pragma once
#include "Employee.hpp"
#include "../Shipment/Provider.hpp"
#include "../Shipment/PurchaseOrder.hpp"
#include "../Construction/Minimarket.hpp"
#include "../Construction/Shelf.hpp"
#include "../Construction/Shkaf.hpp"

/**
 * @class Director
 * @brief Класс директора магазина
 * Наследует Employee и реализует функции управления магазином: контроль готовности, заказ товаров, контроль персонала.
 * @see Employee
 */
class Director : public Employee {
private:
    Minimarket* minimarket;                        /**< Магазин, которым управляет директор */
    StaffDatabase staff;                            /**< База данных персонала */
    std::vector<Shkaf*> shkafs;                    /**< Шкафы магазина */
    std::vector<Product> shopping_list;            /**< Список товаров для заказа */
    std::vector<Provider*> allowed_providers;      /**< Разрешённые поставщики */

public:
    /**
     * @brief Конструктор Director
     * @param name Имя директора
     * @param surname Фамилия директора
     * @param ID Идентификатор директора
     * @param sex Пол директора
     */
    Director(const std::string& name,
             const std::string& surname,
             const std::string& ID,
             SexType sex)
            : Employee(name, surname, ID, sex) {}

    /**
     * @brief Проверка готовности магазина к работе
     */
    void CheckReadinessForWork();

    /**
     * @brief Контроль сроков годности продуктов
     */
    void ProductExpirationDateControl();

    /**
     * @brief Очистка списка покупок
     */
    void ClearShoppingList();

    /**
     * @brief Добавление продукта в список покупок
     * @param product Продукт
     * @param quantity Количество
     */
    void AddToShoppingList(const Product& product, int quantity);

    /**
     * @brief Анализ склада и подготовка заказа на пополнение
     * @param warehouse_state Состояние склада
     * @param minimal_stock Минимальный запас товара (по умолчанию 20)
     */
    void AnalyzeWarehouseAndPrepareOrder(const std::vector<Product>& warehouse_state,
                                         int minimal_stock = 20);

    /**
     * @brief Добавление разрешённого поставщика
     * @param provider Указатель на поставщика
     */
    void AddAllowedProvider(Provider* provider);

    /**
     * @brief Проверка, можно ли заказать у данного поставщика
     * @param provider Поставщик
     * @return true если можно, иначе false
     */
    bool CanOrderFrom(Provider* provider) const;

    /**
     * @brief Создание заказа поставщику
     * @param provider Поставщик
     * @param destination Место доставки
     * @return PurchaseOrder Созданный заказ
     */
    PurchaseOrder CreatePurchaseOrder(Provider* provider,
                                      const std::string& destination);

    /**
     * @brief Отправка заказа поставщику
     * @param order Заказ
     * @return ProductsDelivery Доставка товаров
     */
    ProductsDelivery SendOrderToProvider(PurchaseOrder& order);

    /**
     * @brief Составление графика работы персонала
     */
    void DrawingUpStaffWorkSchedule();

    /**
     * @brief Добавление шкафа в магазин
     * @param shkaf Указатель на шкаф
     */
    void AddShkaf(Shkaf* shkaf);
};
