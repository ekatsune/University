#ifndef MINIMARKET_CARDPAYMENT_HPP
#define MINIMARKET_CARDPAYMENT_HPP

#include "PaymentMethod.hpp"
#include "../Products/Date.hpp"

/**
 * @class CardPayment
 * @brief Класс реализующий оплату картой.
 * @see PaymentMethod
 */
class CardPayment : public PaymentMethod {
private:
    std::string card_number; /**< Номер карты */
    std::string card_holder; /**< Владелец карты */
    Date expiry;             /**< Срок действия карты */

public:
    /**
     * @brief Конструктор CardPayment
     * @param number Номер карты
     * @param holder Имя владельца карты
     * @param exp Срок действия карты
     */
    CardPayment(const std::string& number,
                const std::string& holder,
                const Date& exp)
            : PaymentMethod("Card"),
              card_number(number),
              card_holder(holder),
              expiry(exp) {};

    /**
     * @brief Проверяет корректность карты
     * @return true если карта действительна, иначе false
     */
    bool ValidateCard();

    /**
     * @brief Оплата суммы картой
     * @param amount Сумма оплаты
     * @return true если оплата прошла успешно, иначе false
     */
    bool Pay(const BYN& amount) override;
};

#endif //MINIMARKET_CARDPAYMENT_HPP
