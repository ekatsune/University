#include "ContactInformation.hpp"
/**
 * @file ContactInformation.cpp
 * @brief Реализация класса `ContactInformation`.
 * @details
 * Этот файл содержит реализацию методов класса `ContactInformation`,
 * который моделирует базу данных контактной информации.
 * @author
 * Ekatsune
 */
void ContactInformation::SetPhone(const std::string& phone) { this->phone = phone; }

void ContactInformation::SetEmail(const std::string& email) { this->email = email; }

void ContactInformation::SetAddress(const std::string& address) { this->address = address; }

std::string ContactInformation::GetPhone()  const { return phone; }

std::string ContactInformation::GetEmail()  const { return email; }

std::string ContactInformation::GetAddress() const { return address; }