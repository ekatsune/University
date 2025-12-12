#pragma once
#include <iostream>
#include "Date.hpp"
#include "../Banking/BYN.hpp"

/**
 * @class Product
 * @brief Базовый класс продукта
 * Содержит основную информацию о продукте: название, цену, даты производства и истечения срока годности, состав, вес и количество.
 */
class Product {
protected:
    std::string name;                          /**< Название продукта */
    Date data_of_manufacture;                  /**< Дата производства */
    Date date_of_expiration;                   /**< Дата окончания срока годности */
    BYN price;                                 /**< Цена продукта */
    double discount = 0;                       /**< Процент скидки */
    std::string information_about_the_manufacturer; /**< Информация о производителе */
    std::string storage_rules;                 /**< Правила хранения */
    std::string product_composition;           /**< Состав продукта */
    double unit_weight;                        /**< Вес одной единицы */
    int quantity = 1;                          /**< Количество единиц */

public:
    /** @brief Конструктор с названием и ценой */
    Product(const std::string& name, const BYN& price)
            : name(name), price(price) {}

    /** @brief Конструктор по умолчанию */
    Product() = default;

    /**
     * @brief Конструктор с полной информацией о продукте
     */
    Product(const std::string& name, const Date& dom, const Date& doe, const BYN& price,
            double disc, const std::string& manuf, const std::string& rules,
            const std::string& comp, double weight)
            : name(name), data_of_manufacture(dom), date_of_expiration(doe), price(price),
              discount(disc), information_about_the_manufacturer(manuf),
              storage_rules(rules), product_composition(comp), unit_weight(weight) {}

    /**
     * @brief Конструктор с указанием количества
     */
    Product(const std::string& name, const Date& dom, const Date& doe, const BYN& price,
            const std::string& manuf, const std::string& rules,
            const std::string& comp, double weight, int quantity)
            : name(name), data_of_manufacture(dom), date_of_expiration(doe), price(price),
              information_about_the_manufacturer(manuf), storage_rules(rules),
              product_composition(comp), unit_weight(weight), quantity(quantity) {}

    /** @brief Получить название продукта */
    const std::string& GetName() const;

    /** @brief Получить количество продукта */
    int GetQuantity() const;

    /** @brief Получить цену продукта */
    BYN GetPrice() const;

    /** @brief Получить информацию о производителе */
    std::string GetInformationAboutTheManufacturer() const;

    /** @brief Получить дату производства */
    const Date& GetManufactureDate() const;

    /** @brief Получить дату окончания срока годности */
    const Date& GetExpirationDate() const;

    /** @brief Получить вес одной единицы продукта */
    double GetWeight() const;

    /** @brief Испортить продукт (для тестирования/логики) */
    void GoBad();

    /** @brief Получить правила хранения продукта */
    std::string GetStorageRules();

    /** @brief Получить состав продукта */
    std::string GetProductComposition();

    /**
     * @brief Требуемая температура хранения (переопределяется в наследниках)
     * @return int Температура хранения
     */
    virtual int RequiresTemperature();

    /** @brief Установить количество продукта */
    void SetQuantity(int quantity);

    /** @brief Уменьшить количество продукта на заданное значение */
    void DecreaseQuantity(int quantity);
};
