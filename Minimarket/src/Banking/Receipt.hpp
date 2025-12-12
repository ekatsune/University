#ifndef MINIMARKET_RECEIPT_HPP
#define MINIMARKET_RECEIPT_HPP

#include "../Products/Product.hpp"
#include <vector>

/**
 * @class Receipt
 * @brief Класс чека.
 * Представляет чек покупателя, содержит товары, суммы, метод оплаты и применённые скидки.
 */
class Receipt {
private:
    int receipt_ID;                       /**< ID чека */
    Date date;                            /**< Дата создания чека */
    std::vector<Product*> items;          /**< Список товаров в чеке */
    BYN total;                            /**< Итоговая сумма */
    BYN paid;                             /**< Оплаченная сумма */
    BYN change;                           /**< Сдача покупателю */
    std::string payment_method_name;      /**< Название метода оплаты */
    double discount_applied;              /**< Применённый процент скидки */

public:
    /**
     * @brief Конструктор по умолчанию
     */
    Receipt()
            : receipt_ID(0), total(0), paid(0),
            change(0), discount_applied(0.0), payment_method_name("")
            {};

    /**
     * @brief Конструктор с указанием ID и даты
     * @param id ID чека
     * @param d Дата создания чека
     */
    Receipt(int id, const Date& d)
            : receipt_ID(id), date(d), total(0), paid(0),
            change(0), discount_applied(0.0), payment_method_name("")
            {};

    /**
     * @brief Печать чека на экран
     */
    void Print();

    /**
     * @brief Сохранение чека в файл
     * @param filename Имя файла
     */
    void SaveToFile(std::string filename);

    /**
     * @brief Добавление товара в чек
     * @param product Указатель на товар
     */
    void AddItem(Product* product);

    /**
     * @brief Удаление товара из чека по имени
     * @param name Название товара
     */
    void DeleteItem(const std::string& name);

    /**
     * @brief Получить ID чека в виде строки
     * @return std::string ID чека
     */
    std::string GetId() const;

    /**
     * @brief Получить итоговую сумму
     * @return BYN Итоговая сумма
     */
    BYN GetTotal() const;

    /**
     * @brief Пересчитать итоговую сумму чека
     * @return int Количество товаров
     */
    int CalculateTotals();

    /**
     * @brief Получить дату создания чека
     * @return const Date& Дата
     */
    const Date& GetDate() const;

    /**
     * @brief Получить список товаров в чеке
     * @return const std::vector<Product*>& Список товаров
     */
    const std::vector<Product*>& GetItems() const;

    /**
     * @brief Установить новую итоговую сумму
     * @param new_total Новая сумма
     */
    void SetTotal(const BYN& new_total);

    /**
     * @brief Применить скидку к чеку
     * @param percent Процент скидки
     */
    void AddDiscount(double percent);

    /**
     * @brief Вычесть указанную сумму из итоговой
     * @param value Сумма для вычитания
     */
    void SubtractFromTotal(const BYN& value);
};

#endif //MINIMARKET_RECEIPT_HPP
