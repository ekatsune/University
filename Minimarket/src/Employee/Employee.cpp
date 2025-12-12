#include "string"
#include "Employee.hpp"
/**
 * @file Employee.cpp
 * @brief Реализация класса `Employee`.
 * @details
 * Этот файл содержит реализацию методов класса `Employee`,
 * который моделирует базовый класс для классов-наследников.
 * @author
 * Ekatsune
 */
Employee::Employee(const std::string& name,
                   const std::string& surname,
                   const std::string& ID,
                   sex_type sex)
        : name(name), surname(surname), ID(ID), sex(sex)
{}

std::string Employee::GetID() const {return ID;}

std::string Employee::GetName() const {return name;}

std::string Employee::GetSurname() const {return surname;}

Employee::sex_type Employee::GetSex() const {
    return sex;
}
