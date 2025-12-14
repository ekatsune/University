#pragma once
#include "Employee.hpp"
#include "../Construction/Shelf.hpp"

class Warehouse;

/**
 * @class WarehouseWorker
 * @brief Класс складского работника
 * Наследует Employee и реализует функции приёма товаров, регистрации, отчётов и пополнения полок.
 * @see Employee
 */
class WarehouseWorker : public Employee {
private:
    Warehouse* work_place = nullptr; /**< Ссылка на склад, где работает сотрудник */

public:
    /**
     * @brief Конструктор WarehouseWorker
     * @param name Имя работника
     * @param surname Фамилия работника
     * @param ID Идентификатор работника
     * @param sex Пол работника
     */
    WarehouseWorker(const std::string& name,
                    const std::string& surname,
                    const std::string& ID,
                    Employee::SexType sex)
            : Employee(name, surname, ID, sex) {}

    /**
     * @brief Приём товаров на склад
     * @param name Название продукта
     * @param data_of_manufacture Дата производства
     * @param date_of_expiration Дата истечения срока годности
     * @param price Цена продукта
     * @param information_about_the_manufacturer Информация о производителе
     * @param storage_rules Правила хранения
     * @param product_composition Состав продукта
     * @param unit_weight Вес одной единицы
     * @param quantity Количество единиц
     */
    void AcceptTheProduct(std::string name,
                          Date data_of_manufacture,
                          Date date_of_expiration,
                          BYN price,
                          std::string information_about_the_manufacturer,
                          std::string storage_rules,
                          std::string product_composition,
                          double unit_weight,
                          int quantity);

    /**
     * @brief Регистрация товаров на складе
     * @param filename Имя файла для записи
     */
    void ProductRegistration(const std::string& filename);

    /**
     * @brief Получить текущее состояние склада
     * @return std::vector<Product> Список продуктов на складе
     */
    std::vector<Product> GetWarehouseState() const;

    /**
     * @brief Печать отчёта об остатках на складе
     */
    void WarehouseBalanceReport() const;

    /**
     * @brief Пополнение полок в магазине
     * @param shelf Полка, которую нужно пополнить
     * @param product_name Название продукта
     * @param quantity Количество для пополнения
     */
    void ReplenishmentOfShelvesInMinimarket(Shelf& shelf,
                                            const std::string& product_name,
                                            int quantity);

    /**
     * @brief Установить склад для работы
     * @param warehouse Указатель на склад
     */
    void SetWorkPlace(Warehouse* warehouse);
};
