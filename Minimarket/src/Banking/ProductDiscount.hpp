#ifndef MINIMARKET_PRODUCTDISCOUNT_HPP
#define MINIMARKET_PRODUCTDISCOUNT_HPP

#include "Discount.hpp"

/**
 * @class ProductDiscount
 * @brief Класс скидки для конкретного продукта.
 * Наследует Discount и применяет скидку только к указанному продукту в чеке.
 * @see Discount
 */
class ProductDiscount : public Discount {
private:
    std::string product_name; /**< Название продукта, на который действует скидка */

public:
    /**
     * @brief Конструктор ProductDiscount
     * @param product Название продукта
     * @param name Название скидки
     * @param percent Процент скидки
     * @param start Дата начала действия скидки
     * @param end Дата окончания действия скидки
     */
    ProductDiscount(const std::string& product,
                    const std::string& name,
                    double percent,
                    const Date& start,
                    const Date& end)
            : Discount(name, percent, start, end),
              product_name(product) {}

    /**
     * @brief Применение скидки к чеку.
     * Применяет скидку только к указанному продукту, если он присутствует в чеке.
     * @param receipt Чек, к которому применяется скидка
     */
    void Apply(Receipt& receipt) const override;
};

#endif //MINIMARKET_PRODUCTDISCOUNT_HPP
