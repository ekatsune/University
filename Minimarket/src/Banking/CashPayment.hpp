#ifndef MINIMARKET_CASHPAYMENT_HPP
#define MINIMARKET_CASHPAYMENT_HPP

#include "PaymentMethod.hpp"

/**
 * @class CashPayment
 * @brief Класс реализующий оплату наличными.
 * @see PaymentMethod
 */
class CashPayment : public PaymentMethod {
private:
    BYN cash_given; /**< Переданная сумма наличными */
    BYN change;     /**< Сдача покупателю */

public:
    /**
     * @brief Конструктор CashPayment
     * @param given Сумма, переданная покупателем
     */
    CashPayment(const BYN &given)
            : PaymentMethod("Cash"),
              cash_given(given), change(0) {};

    /**
     * @brief Оплата суммы наличными
     * @param amount Сумма покупки
     * @return true если оплата прошла успешно, иначе false
     */
    bool Pay(const BYN& amount) override;

    /**
     * @brief Проверка, что это оплата наличными
     * @return true
     */
    bool IsCash() const override ;

    /**
     * @brief Установить сумму сдачи
     * @param current_change Сумма сдачи
     */
    void SetChange(BYN current_change);

    /**
     * @brief Получить сумму сдачи
     * @return BYN Сдача
     */
    BYN GetChange() const;

    /**
     * @brief Получить сумму, переданную покупателем
     * @return BYN Переданная сумма
     */
    BYN GetGiven();
};

#endif //MINIMARKET_CASHPAYMENT_HPP
