#include "Shkaf.hpp"
/**
 * @file Shkaf.cpp
 * @brief Реализация класса `Shkaf`.
 * @details
 * Этот файл содержит реализацию методов класса `Shkaf`,
 * который моделирует шкаф с полками.
 * @author
 * Ekatsune
 */
void Shkaf::AddShelf(Shelf* shelf) {
    if (shelves.size() < quantity_of_shelfs) {
        shelves.push_back(shelf);
    } else {
        std::cout << "Невозможно добавить полку: достигнуто максимальное количество\n";
    }
}

void Shkaf::RemoveShelf(int index) {
    if (index < 0 || index >= (int)shelves.size()) {
        std::cout << "Неверный индекс полки\n";
        return;
    }
    delete shelves[index];
    shelves.erase(shelves.begin() + index);
}

Shelf* Shkaf::GetShelf(int index) const {
    if (index < 0 || index >= (int)shelves.size())
        return nullptr;
    return shelves[index];
}

int Shkaf::GetShelfCount() const {
    return shelves.size();
}

void Shkaf::ShowShelves() const {
    std::cout << "Шкаф '" << name << "' содержит "
              << shelves.size() << " полок.\n";
}

const std::string& Shkaf::GetName() const { return name; }

void Shkaf::SetName(const std::string& sh_name) { name = sh_name; }