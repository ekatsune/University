#ifndef MINIMARKET_DISCOUNT_HPP
#define MINIMARKET_DISCOUNT_HPP

#include "BYN.hpp"
#include "Receipt.hpp"

/**@class BYN
 * @brief Базовый класс для скидок.
 * Представляет скидку с указанием процента, даты действия и имени.
 */
class Discount {
protected:
    double percent;       /**< Процент скидки */
    std::string name;     /**< Название скидки */
    Date start_date;      /**< Дата начала действия скидки */
    Date end_date;        /**< Дата окончания действия скидки */

public:
    /**
     * @brief Конструктор скидки
     * @param discount_name Название скидки
     * @param discount_percent Процент скидки
     * @param start Дата начала действия
     * @param end Дата окончания действия
     */
    Discount(const std::string& discount_name,
             double discount_percent,
             const Date& start,
             const Date& end)
            : name(discount_name),
              percent(discount_percent),
              start_date(start),
              end_date(end) {}

    /** @brief Виртуальный деструктор */
    virtual ~Discount() = default;

    /**
     * @brief Проверка активности скидки на указанную дату
     * @param today Текущая дата
     * @return true если скидка активна, иначе false
     */
    bool IsActive(const Date& today) const;

    /**
     * @brief Применение скидки к чеку
     *
     * Абстрактный метод, должен быть реализован в наследниках.
     * @param receipt Чек, к которому применяется скидка
     */
    virtual void Apply(Receipt& receipt) const = 0;

    /** @brief Получить название скидки */
    const std::string& GetName() const;

    /** @brief Получить процент скидки */
    double GetPercent() const;
};

#endif //MINIMARKET_DISCOUNT_HPP
