#ifndef MINIMARKET_PAYMENTMETHOD_HPP
#define MINIMARKET_PAYMENTMETHOD_HPP

#include <string>
#include "BYN.hpp"

/**
 * @class PaymentMethod
 * @brief Абстрактный базовый класс для методов оплаты.
 * Определяет интерфейс для различных способов оплаты, таких как наличные или карта.
 */
class PaymentMethod {
protected:
    std::string name; /**< Название метода оплаты */

public:
    /**
     * @brief Конструктор PaymentMethod
     * @param meth_name Название метода оплаты
     */
    PaymentMethod(const std::string& meth_name) : name(meth_name) {}

    /** @brief Виртуальный деструктор */
    virtual ~PaymentMethod() = default;

    /**
     * @brief Оплата суммы
     * @param amount Сумма оплаты
     * @return true если оплата прошла успешно, иначе false
     */
    virtual bool Pay(const BYN& amount) = 0;

    /**
     * @brief Проверка, является ли метод оплаты наличными
     * @return true если метод оплаты - наличные, иначе false
     */
    virtual bool IsCash() const;

    /**
     * @brief Получить название метода оплаты
     * @return std::string Название метода оплаты
     */
    virtual std::string GetName() const;
};

#endif //MINIMARKET_PAYMENTMETHOD_HPP
