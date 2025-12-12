#ifndef MINIMARKET_TOTALPRICEDISCOUNT_HPP
#define MINIMARKET_TOTALPRICEDISCOUNT_HPP

#include "Discount.hpp"

/**
 * @class TotalPriceDiscount
 * @brief Класс скидки по минимальной сумме корзины.
 * Наследует Discount и применяет скидку, если сумма чека превышает заданный порог.
 * @see Discount
 */
class TotalPriceDiscount : public Discount {
private:
    BYN threshold; /**< Минимальная сумма корзины для применения скидки */

public:
    /**
     * @brief Конструктор TotalPriceDiscount
     * @param min_sum Минимальная сумма корзины
     * @param name Название скидки
     * @param percent Процент скидки
     * @param start Дата начала действия скидки
     * @param end Дата окончания действия скидки
     */
    TotalPriceDiscount(const BYN& min_sum,
                       const std::string& name,
                       double percent,
                       const Date& start,
                       const Date& end)
            : Discount(name, percent, start, end),
              threshold(min_sum) {}

    /**
     * @brief Применение скидки к чеку
     *
     * Скидка применяется только если сумма чека >= threshold.
     * @param receipt Чек, к которому применяется скидка
     */
    void Apply(Receipt& receipt) const override;
};

#endif //MINIMARKET_TOTALPRICEDISCOUNT_HPP
