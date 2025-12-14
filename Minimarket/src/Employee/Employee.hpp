#pragma once
#include <iostream>
#include "ContactInformation.hpp"
#include "WorkSchedule.hpp"

/**
 * @class Employee
 * @brief Базовый класс сотрудника
 * Содержит основную информацию о сотруднике: имя, фамилия, ID, пол, контактную информацию и график работы.
 */
class Employee {
public:
    /**
     * @brief Пол сотрудника
     */
    enum class SexType { male, female };

protected:
    const std::string name;        /**< Имя сотрудника */
    const std::string surname;     /**< Фамилия сотрудника */
    const std::string ID;          /**< Идентификатор сотрудника */
    const SexType sex;            /**< Пол сотрудника */
    WorkSchedule schedule;         /**< График работы сотрудника */
    ContactInformation contact;    /**< Контактная информация сотрудника */

public:
    /**
     * @brief Конструктор Employee
     * @param name Имя сотрудника
     * @param surname Фамилия сотрудника
     * @param ID Идентификатор сотрудника
     * @param sex Пол сотрудника
     */
    Employee(const std::string& name,
             const std::string& surname,
             const std::string& ID,
             SexType sex);

    /**
     * @brief Получить имя сотрудника
     * @return std::string Имя
     */
    std::string GetName() const;

    /**
     * @brief Получить фамилию сотрудника
     * @return std::string Фамилия
     */
    std::string GetSurname() const;

    /**
     * @brief Получить идентификатор сотрудника
     * @return std::string ID
     */
    std::string GetID() const;

    /**
     * @brief Получить пол сотрудника
     * @return SexType Пол
     */
    SexType GetSex() const;
};
