#pragma once
#include <iostream>
#include <vector>
#include "Cart.hpp"
#include "../Products/Product.hpp"
#include "../Employee/Cashier.hpp"

/**
 * @class Customer
 * @brief Класс покупателя
 * Представляет покупателя с кошельком, корзиной и возможностью совершать покупки.
 */
class Customer {
public:
    /**
     * @brief Категории возраста покупателя
     */
    enum class CategoryAge {
        up_to_15,           /**< До 15 лет */
        after_15_up_to_18,  /**< От 15 до 18 лет */
        after_18            /**< Старше 18 лет */
    };

private:
    BYN wallet;               /**< Деньги покупателя */
    Cart cart;                /**< Корзина покупателя */
    CategoryAge age;         /**< Возрастная категория */
    Cashier* cashier;         /**< Кассир, обслуживающий покупателя */

public:
    /**
     * @brief Конструктор Customer
     * @param wallet Сумма денег у покупателя
     * @param age Возрастная категория покупателя
     */
    Customer(BYN wallet, CategoryAge age)
            : wallet(wallet), age(age) {};

    /**
     * @brief Совершить оплату товаров из корзины
     */
    void Payment();

    /**
     * @brief Добавить товар в корзину
     * @param product Указатель на продукт
     */
    void AddProductToCart(Product* product);

    /**
     * @brief Удалить товар из корзины по имени
     * @param name Название товара
     */
    void RemoveProductFromCart(const std::string& name);

    /**
     * @brief Показать содержимое корзины
     */
    void ShowCart() const;

    /**
     * @brief Получить все товары в корзине
     * @return const std::vector<Product*>& Список товаров
     */
    const std::vector<Product*>& GetCartItems() const;

    /**
     * @brief Получить возрастную категорию покупателя
     * @return category_age Категория возраста
     */
    CategoryAge GetAge() const;

    /**
     * @brief Назначить кассира, который обслуживает покупателя
     * @param cashier Указатель на кассира
     */
    void SetCashier(Cashier * cashier);

    /**
     * @brief Получить корзину покупателя
     * @return Cart& Ссылка на корзину
     */
    Cart& GetCart();
};
