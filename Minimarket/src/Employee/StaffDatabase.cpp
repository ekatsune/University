#include "StaffDatabase.hpp"
/**
 * @file StaffDatabase.cpp
 * @brief Реализация класса `StaffDatabase`.
 * @details
 * Этот файл содержит реализацию методов класса `StaffDatabase`,
 * который моделирует базу данных о сотрудниках.
 * @author
 * Ekatsune
 */
void StaffDatabase::AddEmployee(Employee *employee)  {
    employees.push_back(employee);
}

int StaffDatabase::GetEmployeeCount() const {
    return static_cast<int>(employees.size());
}

const std::vector<Employee *> &StaffDatabase::GetEmployees() const {return employees;}

void StaffDatabase::RemoveEmployee(const std::string &id) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->GetID() == id) {
            employees.erase(it);
            return;
        }
    }
}

Employee* StaffDatabase::FindEmployeeByID(const std::string& id) const {
    for (auto* employee : employees) {
        if (employee && employee->GetID() == id) {
            return employee;
        }
    }
    return nullptr;
}
