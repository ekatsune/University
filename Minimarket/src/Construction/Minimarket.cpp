#include "Minimarket.hpp"
/**
 * @file Minimarket.cpp
 * @brief Реализация класса `Minimarket`.
 * @details
 * Этот файл содержит реализацию методов класса `Minimarket`,
 * который моделирует работу минимаркета.
 * @author
 * Ekatsune
 */
void Minimarket::HireEmployee() {
    std::string empl_name, surname, id; int sex;
    std::cout << "Введите имя: ";
    std::cin >> empl_name;
    std::cout << "Введите фамилию: ";
    std::cin >> surname;
    std::cout << "Введите ID: ";
    std::cin >> id;
    std::cout << "Введите пол (0 - мужчина, 1 - женщина): ";
    std::cin >> sex;
    auto* employee = new Employee(
            empl_name,
            surname,
            id,
            sex == 0 ? Employee::SexType::male : Employee::SexType::female
    );
    staff.AddEmployee(employee);
    std::cout << "Сотрудник нанят!\n";
}

void Minimarket::FireEmployee() {
    std::string id;
    std::cout << "Введите ID сотрудника для увольнения: ";
    std::cin >> id;
    staff.RemoveEmployee(id);
    std::cout << "Сотрудник уволен.\n";
}

void Minimarket::SetStatus(Minimarket::StoreStatus StoreStatus) {
    this->current_status=StoreStatus;
}

Minimarket::StoreStatus Minimarket::GetStatus(){return current_status;}

StaffDatabase& Minimarket::GetStaffDatabase() { return staff; }

void Minimarket::ShowTradingFloor() const { trading_floor.ShowAllShelves(); }