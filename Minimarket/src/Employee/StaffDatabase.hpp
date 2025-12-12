//
// Created by ekatsune on 30.11.2025.
//

#ifndef MINIMARKET_STAFFDATABASE_HPP
#define MINIMARKET_STAFFDATABASE_HPP

#include "Employee.hpp"
#include <vector>

/**
 * @class StaffDatabase
 * @brief Класс базы данных сотрудников
 * Управляет списком сотрудников: добавление, удаление и поиск.
 */
class StaffDatabase {
private:
    std::vector<Employee*> employees; /**< Список сотрудников */

public:
    /**
     * @brief Добавить сотрудника в базу данных
     * @param employee Указатель на сотрудника
     */
    void AddEmployee(Employee* employee);

    /**
     * @brief Удалить сотрудника по ID
     * @param id Идентификатор сотрудника
     */
    void RemoveEmployee(const std::string& id);

    /**
     * @brief Получить количество сотрудников
     * @return int Количество сотрудников
     */
    int GetEmployeeCount() const;

    /**
     * @brief Получить список всех сотрудников
     * @return const std::vector<Employee*>& Список сотрудников
     */
    const std::vector<Employee*>& GetEmployees() const;

    /**
     * @brief Найти сотрудника по ID
     * @param id Идентификатор сотрудника
     * @return Employee* Указатель на сотрудника или nullptr, если не найден
     */
    Employee* FindEmployeeByID(const std::string& id) const;
};

#endif //MINIMARKET_STAFFDATABASE_HPP
