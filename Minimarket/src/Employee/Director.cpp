#include "Director.hpp"
#include "../Exceptions/MinimarketException.hpp"
/**
 * @file Director.cpp
 * @brief Реализация класса `Director`.
 * @details
 * Этот файл содержит реализацию методов класса `Director`,
 * который моделирует работу директора минимаркета.
 * @author
 * Ekatsune
 */
void Director::ClearShoppingList() { shopping_list.clear(); }

void Director::AddToShoppingList(const Product& p, int quantity) {
    Product copy = p;
    copy.SetQuantity(quantity);
    shopping_list.push_back(copy);
}

void Director::AnalyzeWarehouseAndPrepareOrder(const std::vector<Product>& warehouse_state,
                                     int minimal_stock){
    ClearShoppingList();

    for (const auto& product : warehouse_state) {
        if (product.GetQuantity() < minimal_stock) {
            int to_order = minimal_stock * 2 - product.GetQuantity();
            AddToShoppingList(product, to_order);
            std::cout << "Добавлено в список закупок: "
                      << product.GetName()
                      << " x" << to_order << "\n";
        }
    }

    if (shopping_list.empty())
        std::cout << "Все товары в достаточном количестве.\n";
}

void Director::AddAllowedProvider(Provider* provider) {
    allowed_providers.push_back(provider);
}

bool Director::CanOrderFrom(Provider* p) const {
    for (auto prov : allowed_providers)
        if (prov == p) return true;
    return false;
}

PurchaseOrder Director::CreatePurchaseOrder(Provider* provider,
                                  const std::string& destination)
{
    if (!CanOrderFrom(provider)) throw UnauthorizedProviderException();

    if (shopping_list.empty()) throw EmptyPurchaseListException();

    PurchaseOrder order(provider,shopping_list,destination);

    order.GenerateOrderID();
    order.SetStatus(PurchaseOrder::Status::Approved);

    std::cout << "Заказ успешно создан директором!\n";
    return order;
}

ProductsDelivery Director::SendOrderToProvider(PurchaseOrder& order) {
    if (order.GetSupplier() == nullptr) throw InvalidSupplierException();

    std::cout << "Отправка заказа поставщику...\n";
    return order.GetSupplier()->StartDelivery(order);
}

void Director::CheckReadinessForWork() {
    std::cout << "Проверка готовности магазина...\n";
    Minimarket::StoreStatus status = minimarket->GetStatus();
    if (status == Minimarket::StoreStatus::CLOSE || status == Minimarket::StoreStatus::SANITARY_DAY) {
        std::cout << "Магазин закрыт. Готовность: НЕТ\n"; return;
    }
    else if (status == Minimarket::StoreStatus::LUNCH_BREAK) {
        std::cout << "Сейчас обеденный перерыв. Магазин частично готов.\n";
    } else if (status == Minimarket::StoreStatus::OPEN) {
        std::cout << "Магазин открыт.\n";
    }
    const auto& employees = staff.GetEmployees();
    if (employees.empty()) {
        std::cout << "Ошибка: нет сотрудников на смене!\n";
    } else {
        std::cout << "Количество сотрудников на смене: " << employees.size() << "\n";
    }
    if (status == Minimarket::StoreStatus::OPEN && !employees.empty() && !shopping_list.empty()) {
        std::cout << "Магазин полностью готов к работе.\n";
    } else {
        std::cout << "Магазин не полностью готов к работе.\n";
    }
}

void Director::DrawingUpStaffWorkSchedule() {
    std::cout << "Составление графика работы персонала...\n";
    WorkSchedule schedule;
    for (int d = 0; d < static_cast<int>(WorkSchedule::Day::Count); ++d) {
        std::string hours = "09:00-18:00";
        if (d == static_cast<int>(WorkSchedule::Day::Saturday) || d == static_cast<int>(WorkSchedule::Day::Sunday)) {
            hours = "10:00-16:00";
        }
        schedule.SetDay(static_cast<WorkSchedule::Day>(d), hours);
    }
    schedule.Print();
}

void Director::ProductExpirationDateControl() {
    for (size_t i = 0; i < shkafs.size(); ++i) {
        Shkaf* shkaf = shkafs[i];
        if (!shkaf) continue;

        int shelfCount = shkaf->GetShelfCount();
        for (int j = 0; j < shelfCount; ++j) {
            Shelf* shelf = shkaf->GetShelf(j);
            if (!shelf) continue;

            const auto& products = shelf->GetAllProducts();
            for (Product* product : products) {
                if (!product) continue;
                Date today;
                if (product->GetExpirationDate() < today) throw ExpiredProductException(name, i, j);
            }
        }
    }
}

void Director::AddShkaf(Shkaf* shkaf) {
    shkafs.push_back(shkaf);
}

