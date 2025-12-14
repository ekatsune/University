#pragma once
#include "Employee.hpp"
#include "CleaningSchedule.hpp"

/**
 * @class Cleaner
 * @brief Класс уборщика
 * Наследует Employee и реализует функции уборки, включая вынос мусора и влажную уборку по графику.
 * @see Employee
 */
class Cleaner : public Employee {
private:
    int garbage_bags = 0;                  /**< Количество мешков с мусором */
    CleaningSchedule cleaningSchedule;     /**< График уборки */

public:
    /**
     * @brief Конструктор Cleaner
     * @param name Имя уборщика
     * @param surname Фамилия уборщика
     * @param ID Идентификатор уборщика
     * @param sex Пол уборщика
     */
    Cleaner(const std::string& name,
            const std::string& surname,
            const std::string& ID,
            SexType sex)
            : Employee(name, surname, ID, sex) {}

    /**
     * @brief Сбор и вынос мусора
     */
    void GarbageRemoval();

    /**
     * @brief Влажная уборка по графику
     * @param day День недели из графика работы
     */
    void Cleaning(WorkSchedule::Day day);

    /**
     * @brief Получить график уборки (для изменения)
     * @return CleaningSchedule& Ссылка на график уборки
     */
    CleaningSchedule& GetCleaningSchedule();

    /**
     * @brief Получить график уборки (только для чтения)
     * @return const CleaningSchedule& Константная ссылка на график уборки
     */
    const CleaningSchedule& GetCleaningSchedule() const;
};
