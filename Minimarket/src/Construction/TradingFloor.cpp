#include "TradingFloor.hpp"
#include <algorithm>
/**
 * @file TradingFloor.cpp
 * @brief Реализация класса `TradingFloor`.
 * @details
 * Этот файл содержит реализацию методов класса `TradingFloor`,
 * который моделирует процессы на этаже/зоне минимаркета.
 * @author
 * Ekatsune
 */
void TradingFloor::AddShkaf(Shkaf* shkaf) {
    shkafs.push_back(shkaf);
}

void TradingFloor::RemoveShkaf(int index) {
    if (index < 0 || index >= (int)shkafs.size()) {
        std::cout << "Ошибка: Неверный индекс шкафа\n";
        return;
    }
    delete shkafs[index];
    shkafs.erase(shkafs.begin() + index);
}

void TradingFloor::ShowAllShelves() const {
    std::cout << "Зона: " << zoneName << "\n";
    std::cout << "Количество шкафов: " << shkafs.size() << "\n";

    for (size_t i = 0; i < shkafs.size(); i++) {
        std::cout << "  Шкаф #" << i << ":\n";
        shkafs[i]->ShowShelves();
    }
}

const std::vector<Shkaf*>& TradingFloor::GetShkafs() const {
    return shkafs;
}

void TradingFloor::AddCustomer(Customer* customer) {
    customers.push_back(customer);
}

void TradingFloor::RemoveCustomer(Customer* customer) {
    customers.erase(
            std::remove(customers.begin(), customers.end(), customer),
            customers.end()
    );
}

void TradingFloor::ShowCustomers() const {
    std::cout << "Покупатели на этаже " << floorNumber << ":\n";
    for (const auto* c : customers) {
        std::cout << "  Покупатель, возрастная категория: ";
        switch (c->GetAge()) {
            case Customer::category_age::up_to_15:
                std::cout << "до 15\n";
                break;
            case Customer::category_age::after_15_up_to_18:
                std::cout << "15-18\n";
                break;
            case Customer::category_age::after_18:
                std::cout << "18+\n";
                break;
        }
    }
}

// ---------------------------- ЛОГИКА С ТОВАРАМИ ----------------------------

// Поиск товара на всём торговом этаже
Product* TradingFloor::FindProduct(const std::string& name) {
    for (auto* shkaf : shkafs) {
        int shelfCount = shkaf->GetShelfCount();
        for (int i = 0; i < shelfCount; i++) {
            Shelf* shelf = shkaf->GetShelf(i);
            if (!shelf) continue;

            Product* product = shelf->FindByName(name);
            if (product) return product;
        }
    }
    return nullptr;
}

// Перемещение товара между полками
bool TradingFloor::MoveProduct(const std::string& name, Shelf* from, Shelf* to) {
    if (!from || !to) return false;

    Product* p = from->FindByName(name);
    if (!p) return false;

    from->RemoveProduct(name); // нужно реализовать в Shelf
    to->AddProduct(p);
    return true;
}
