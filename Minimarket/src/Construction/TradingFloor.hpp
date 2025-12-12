#ifndef MINIMARKET_TRADINGFLOOR_HPP
#define MINIMARKET_TRADINGFLOOR_HPP

#include "Shelf.hpp"
#include "Shkaf.hpp"
#include "../Customer/Customer.hpp"

/**
 * @class TradingFloor
 * @brief Класс торгового зала (этаж/зона)
 * Управляет шкафами, полками, продуктами и присутствующими покупателями.
 */
class TradingFloor {
private:
    const int floorNumber = 1;          /**< Номер этажа или зала */
    std::string zoneName;               /**< Название зоны, например "Молочный отдел" */
    double area;                        /**< Площадь торгового зала */
    std::vector<Shkaf*> shkafs;         /**< Шкафы на торговом этаже */
    std::vector<Customer*> customers;   /**< Покупатели, находящиеся на этаже */

public:
    /**
     * @brief Добавить шкаф на торговый этаж
     * @param shkaf Указатель на шкаф
     */
    void AddShkaf(Shkaf* shkaf);

    /**
     * @brief Удалить шкаф по индексу
     * @param index Индекс шкафа
     */
    void RemoveShkaf(int index);

    /**
     * @brief Показать все полки на шкафах торгового этажа
     */
    void ShowAllShelves() const;

    /**
     * @brief Добавить покупателя на торговый этаж
     * @param customer Указатель на покупателя
     */
    void AddCustomer(Customer* customer);

    /**
     * @brief Удалить покупателя с торгового этажа
     * @param customer Указатель на покупателя
     */
    void RemoveCustomer(Customer* customer);

    /**
     * @brief Показать всех покупателей на торговом этаже
     */
    void ShowCustomers() const;

    /**
     * @brief Переместить продукт с одной полки на другую
     * @param name Название продукта
     * @param from Исходная полка
     * @param to Целевая полка
     * @return true если перемещение прошло успешно, иначе false
     */
    bool MoveProduct(const std::string& name, Shelf* from, Shelf* to);

    /**
     * @brief Найти продукт на торговом этаже по имени
     * @param name Название продукта
     * @return Product* Указатель на продукт или nullptr, если не найден
     */
    Product* FindProduct(const std::string& name);

    /**
     * @brief Получить список шкафов на торговом этаже
     * @return const std::vector<Shkaf*>& Список шкафов
     */
    const std::vector<Shkaf*>& GetShkafs() const;
};

#endif //MINIMARKET_TRADINGFLOOR_HPP
