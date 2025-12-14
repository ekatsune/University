#include "Customer.hpp"
/**
 * @file Customer.cpp
 * @brief Реализация класса `Customer`.
 * @details
 * Этот файл содержит реализацию методов класса `Customer`,
 * который моделирует действия покупателя.
 * @author
 * Ekatsune
 */
void Customer::AddProductToCart(Product* product) {
    if (!product) {
        std::cout << "Ошибка: нельзя добавить NULL продукт.\n";
        return;
    }
    cart.AddItem(product);
}

void Customer::RemoveProductFromCart(const std::string& name) {
    try {
        cart.RemoveItem(name);
    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
}

void Customer::ShowCart() const {
    const auto& items = cart.GetItems();
    if (items.empty()) {
        std::cout << "  (пусто)\n";
        return;
    }

    for (auto* p : items) {
        if (p)
            std::cout << "  - " << p->GetName();
    }
}

void Customer::Payment() {
    if (!cashier) {
        std::cout << "Ошибка: кассир не назначен!\n";
        return;
    }
    if (cart.GetItems().empty()) {
        std::cout << "Корзина пуста, платить нечего.\n";
        return;
    }
    cashier->CustomerService(cart);
    cart.Clear();
}

Customer::CategoryAge Customer::GetAge() const {
    return age;
}

const std::vector<Product*>& Customer::GetCartItems() const {
    return cart.GetItems();
}

Cart& Customer::GetCart() { return cart; }

void Customer::SetCashier(Cashier * cashier) {
    this->cashier = cashier;
}
