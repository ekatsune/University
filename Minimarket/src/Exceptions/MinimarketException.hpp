#ifndef MINIMARKET_MINIMARKETEXCEPTION_HPP
#define MINIMARKET_MINIMARKETEXCEPTION_HPP

#include <exception>
#include <string>

/**
 * @class MinimarketException
 * @brief Базовый класс всех исключений, используемых в мини-маркете.
 *
 * Наследует std::exception и предоставляет общий механизм хранения сообщения ошибки.
 */
class MinimarketException : public std::exception {
protected:
    std::string message;
public:
    /**
     * @brief Конструктор исключения.
     * @param msg Сообщение об ошибке.
     */
    explicit MinimarketException(std::string msg)
            : message(std::move(msg)) {}

    /**
     * @brief Получить текст сообщения об ошибке.
     * @return C-строка с описанием ошибки.
     */
    const char* what() const noexcept override {
        return message.c_str();
    }
};

/**
 * @class CardExpiredException
 * @brief Исключение: срок действия карты истёк.
 * @see MinimarketException
 */
class CardExpiredException : public MinimarketException {
public:
    /**
     * @param card_number Номер просроченной карты.
     */
    explicit CardExpiredException(const std::string& card_number)
            : MinimarketException("Ошибка: срок действия карты \"" + card_number + "\" истёк.") {}
};

/**
 * @class NotEnoughCashException
 * @brief Исключение: недостаточно наличных для оплаты.
 * @see MinimarketException
 */
class NotEnoughCashException : public MinimarketException {
public:
    /**
     * @param given Сумма, которую передал покупатель.
     * @param needed Необходимая сумма.
     */
    NotEnoughCashException(double given, double needed)
            : MinimarketException(
            "Недостаточно наличных: дано " + std::to_string(given) +
            " BYN, требуется " + std::to_string(needed) + " BYN."
    ) {}
};

/**
 * @class CashRegisterClosedException
 * @brief Исключение: попытка выполнить операцию при закрытой кассе.
 * @see MinimarketException
 */
class CashRegisterClosedException : public MinimarketException {
public:
    CashRegisterClosedException()
            : MinimarketException("Ошибка: касса закрыта, операция невозможна.") {}
};

/**
 * @class EmptyCartException
 * @brief Исключение: попытка оформить пустую корзину.
 * @see MinimarketException
 */
class EmptyCartException : public MinimarketException {
public:
    EmptyCartException()
            : MinimarketException("Ошибка: корзина пуста — нечего оформлять в чек.") {}
};

/**
 * @class ProductNotFoundException
 * @brief Исключение: товар не найден.
 * @see MinimarketException
 */
class ProductNotFoundException : public MinimarketException {
public:
    /**
     * @param name Название искомого товара.
     */
    explicit ProductNotFoundException(const std::string& name)
            : MinimarketException("Товар \"" + name + "\" не найден.") {}
};

/**
 * @class NullProductException
 * @brief Исключение: попытка добавить пустой (NULL) продукт.
 * @see MinimarketException
 */
class NullProductException : public MinimarketException {
public:
    NullProductException()
            : MinimarketException("Ошибка: попытка добавить NULL-продукт.") {}
};

/**
 * @class UnauthorizedProviderException
 * @brief Исключение: директор не может работать с данным поставщиком.
 * @see MinimarketException
 */
class UnauthorizedProviderException : public MinimarketException {
public:
    UnauthorizedProviderException()
            : MinimarketException("Ошибка: директор не может заказывать у данного поставщика.") {}
};

/**
 * @class EmptyPurchaseListException
 * @brief Исключение: список закупаемых товаров пуст.
 * @see MinimarketException
 */
class EmptyPurchaseListException : public MinimarketException {
public:
    EmptyPurchaseListException()
            : MinimarketException("Ошибка: список закупаемых товаров пуст.") {}
};

/**
 * @class InvalidSupplierException
 * @brief Исключение: заказ не имеет валидного поставщика.
 * @see MinimarketException
 */
class InvalidSupplierException : public MinimarketException {
public:
    InvalidSupplierException()
            : MinimarketException("Ошибка: заказ не имеет поставщика.") {}
};

/**
 * @class ExpiredProductException
 * @brief Исключение: товар просрочен.
 * @see MinimarketException
 */
class ExpiredProductException : public MinimarketException {
public:
    /**
     * @param name Название товара.
     * @param shkaf Номер шкафа.
     * @param shelf Номер полки.
     */
    explicit ExpiredProductException(const std::string& name, int shkaf, int shelf)
            : MinimarketException(
            "Ошибка: товар \"" + name + "\" на шкафу \""
            + std::to_string(shkaf) + "\" на полке \""
            + std::to_string(shelf) + "\" просрочен."
    ) {}
};

/**
 * @class ShiftAlreadyOpenException
 * @brief Исключение: попытка открыть уже открытую смену.
 * @see MinimarketException
 */
class ShiftAlreadyOpenException : public MinimarketException {
public:
    ShiftAlreadyOpenException()
            : MinimarketException("Ошибка: смена уже открыта.") {}
};

/**
 * @class ShiftNotOpenException
 * @brief Исключение: попытка закрыть неоткрытую смену.
 * @see MinimarketException
 */
class ShiftNotOpenException : public MinimarketException {
public:
    ShiftNotOpenException()
            : MinimarketException("Ошибка: смена не открыта, закрыть нельзя.") {}
};

/**
 * @class ReceiptCreationException
 * @brief Исключение: ошибка при создании чека.
 * @see MinimarketException
 */
class ReceiptCreationException : public MinimarketException {
public:
    /**
     * @param reason Описание причины ошибки.
     */
    explicit ReceiptCreationException(const std::string& reason)
            : MinimarketException("Ошибка создания чека: " + reason) {}
};

#endif //MINIMARKET_MINIMARKETEXCEPTION_HPP
