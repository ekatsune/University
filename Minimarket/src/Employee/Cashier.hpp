#pragma once
#include "Employee.hpp"
#include "../Banking/CashRegister.hpp"
#include "../Banking/PaymentMethod.hpp"
#include "../Banking/CashPayment.hpp"
#include "../Banking/CardPayment.hpp"

/**
 * @class Cashier
 * @brief Класс кассира
 * Наследует Employee и реализует функционал кассира: работу с кассой, создание чеков и обслуживание покупателей.
 * @see Employee
 */
class Cashier : public Employee {
private:
    CashRegister cash_register; /**< Касса, которой управляет кассир */

    /**
     * @brief Запрос информации о карте у покупателя
     * @return PaymentMethod* Метод оплаты картой
     */
    PaymentMethod* AskCardInfo();

public:
    /**
     * @brief Конструктор Cashier
     * @param name Имя кассира
     * @param surname Фамилия кассира
     * @param ID Идентификатор кассира
     * @param sex Пол кассира
     */
    Cashier(const std::string& name,
            const std::string& surname,
            const std::string& ID,
            SexType sex)
            : Employee(name, surname, ID, sex), cash_register() {}

    /**
     * @brief Получить кассу кассира
     * @return CashRegister Объект кассы
     */
    CashRegister GetCashRegister();

    /**
     * @brief Получить текст кассового отчёта
     * @return std::string Текст отчёта
     */
    std::string CashReportText() const;

    /**
     * @brief Провести кассовый отчёт
     */
    void CashReport();

    /**
     * @brief Создать чек на основе корзины покупателя
     * @param cart Корзина покупателя
     * @return Receipt Созданный чек
     */
    Receipt CreatingReceipt(const Cart& cart);

    /**
     * @brief Обслуживание покупателя
     * @param cart Корзина покупателя
     */
    void CustomerService(Cart &cart);

    /**
     * @brief Выбор метода оплаты
     * @return PaymentMethod* Выбранный метод оплаты
     */
    PaymentMethod* AskPaymentMethod();

    /**
     * @brief Оплата картой
     * @param total Сумма к оплате
     * @param method Метод оплаты картой
     * @return true если оплата успешна, иначе false
     */
    bool CardPaymentMethod(BYN total, CardPayment& method);

    /**
     * @brief Оплата наличными
     * @param total Сумма к оплате
     * @param method Метод оплаты наличными
     * @return true если оплата успешна, иначе false
     */
    bool CashPaymentMethod(BYN total, CashPayment& method);

    /**
     * @brief Проведение оплаты
     * @param receipt Чек
     * @param method Метод оплаты
     * @return true если оплата успешна, иначе false
     */
    bool ProcessPayment(Receipt& receipt, PaymentMethod& method);

    /**
     * @brief Удаление продукта из чека
     * @param receipt Чек, из которого удаляется продукт
     */
    void CancellationOfProduct(Receipt &receipt);

    /**
     * @brief Открытие смены кассира
     */
    void OpenShift();
};
