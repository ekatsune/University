#pragma once
#include <iostream>
#include <vector>
#include "BYN.hpp"
#include "Receipt.hpp"
#include "../Customer/Cart.hpp"

/**
 * @class CashRegister
 * @brief Класс реализующий модель кассового аппарата.
 */
class CashRegister {
private:
    BYN cash_inside;                 /**< Текущая сумма наличных в кассе */
    std::vector<Receipt> receipts;   /**< Все чеки, созданные кассой */
    bool is_open;                    /**< Состояние смены кассы */
    std::string cashier_id;          /**< ID кассира, который открыл смену */

public:
    /**
     * @brief Конструктор по умолчанию.
     * Инициализирует кассу с нулевой суммой и закрытой сменой.
     */
    CashRegister() : cash_inside(0,0), is_open(false), cashier_id("") {}

    /**
     * @brief Открытие смены кассы
     * @param cashier_id ID кассира
     */
    void OpenShift(std::string cashier_id);

    /**
     * @brief Закрытие смены кассы
     */
    void CloseShift();

    /**
     * @brief Создать чек на основе корзины покупателя
     * @param cart Корзина покупателя
     * @return Receipt Созданный чек
     */
    Receipt CreateReceipt(const Cart& cart);

    /**
     * @brief Получить все чеки, созданные кассой
     * @return const std::vector<Receipt>& Список чеков
     */
    const std::vector<Receipt>& GetReceipts() const;

    /**
     * @brief Получить общую сумму наличных в кассе
     * @return BYN Общая сумма наличных
     */
    BYN GetTotalCash() const;

    /**
     * @brief Добавить наличные в кассу
     * @param amount Сумма для добавления
     */
    void AddCash(const BYN& amount);

    /**
     * @brief Проверить, хватает ли наличных для выдачи
     * @param amount Сумма для проверки
     * @return true если наличных достаточно, иначе false
     */
    bool HasEnoughCash(const BYN& amount) const;

    /**
     * @brief Проверить, открыта ли смена кассы
     * @return true если смена открыта, иначе false
     */
    bool IsShiftOpen();
};
