#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../Warehouse/Warehouse.hpp"
#include "../Employee/StaffDatabase.hpp"
#include "TradingFloor.hpp"

/**
 * @class Minimarket
 * @brief Класс минимаркета
 * Управляет торговым залом, персоналом и текущим статусом магазина.
 */
class Minimarket {
public:
    TradingFloor trading_floor; /**< Торговый зал магазина */

    /**
     * @brief Статус магазина
     */
    enum class StoreStatus {
        OPEN,          /**< Магазин открыт */
        CLOSE,         /**< Магазин закрыт */
        LUNCH_BREAK,   /**< Перерыв на обед */
        SANITARY_DAY   /**< Санитарный день */
    };

private:
    const std::string name;         /**< Название магазина */
    const std::string address;      /**< Адрес магазина */
    StaffDatabase staff;            /**< База сотрудников */
    StoreStatus current_status = StoreStatus::CLOSE; /**< Текущий статус магазина */

public:
    /**
     * @brief Конструктор Minimarket
     * @param name Название магазина
     * @param address Адрес магазина
     */
    Minimarket(const std::string& name,
               const std::string& address)
            : name(name), address(address) {};

    /**
     * @brief Нанять сотрудника
     */
    void HireEmployee();

    /**
     * @brief Уволить сотрудника
     */
    void FireEmployee();

    /**
     * @brief Получить текущий статус магазина
     * @return store_status Текущий статус
     */
    StoreStatus GetStatus();

    /**
     * @brief Получить базу данных сотрудников
     * @return StaffDatabase& Ссылка на базу данных сотрудников
     */
    StaffDatabase& GetStaffDatabase();

    /**
     * @brief Установить текущий статус магазина
     * @param store_status Новый статус
     */
    void SetStatus(Minimarket::StoreStatus store_status);

    /**
     * @brief Показать торговый зал
     */
    void ShowTradingFloor() const;
};
