#include "PurchaseOrder.hpp"
/**
 * @file PurchaseOrder.cpp
 * @brief Реализация класса `PurchaseOrder`.
 * @details
 * Этот файл содержит реализацию методов класса `PurchaseOrder`,
 * который моделирует создание заказа на поставку.
 * @author
 * Ekatsune
 */
void PurchaseOrder::GenerateOrderID() {
    order_id = "ORD-" + std::to_string(std::rand() % 900000 + 100000);
}

Provider* PurchaseOrder::GetSupplier() const { return provider; }

const std::vector<Product>& PurchaseOrder::GetProducts() const { return ordered_products; }

const std::string& PurchaseOrder::GetDestination() const { return destination_warehouse; }

std::string PurchaseOrder::StatusToString(Status status) const {
    switch (status) {
        case Status::Draft: return "Черновик";
        case Status::Approved: return "Одобрен";
        case Status::Rejected: return "Отклонён";
        case Status::InDelivery: return "В пути";
        case Status::Delivered: return "Доставлено";
    }
    return "Неизвестно";
}

void PurchaseOrder::AddProduct(const Product& product) {
    ordered_products.push_back(product);
    RecalculateTotal();
}

bool PurchaseOrder::RemoveProduct(const std::string& product_name) {

    for (auto it = ordered_products.begin(); it != ordered_products.end(); ++it) {
        if (it->GetName() == product_name) {
            ordered_products.erase(it);
            RecalculateTotal();
            return true;
        }
    }
    return false;
}

void PurchaseOrder::RecalculateTotal() {
    total_cost = 0;
    for (const auto& product : ordered_products) {
        total_cost += product.GetPrice();
    }
}

void PurchaseOrder::SetDestination(const std::string& warehouse) {
    destination_warehouse = warehouse;
}

bool PurchaseOrder::IsValid() const {
    return !ordered_products.empty() && provider != nullptr;
}

void PurchaseOrder::SetStatus(Status new_status) {
    order_status = new_status;
}

double PurchaseOrder::GetTotalWeight() const {
    double w = 0;
    for (auto& p : ordered_products)
        w += p.GetWeight();
    return w;
}

BYN PurchaseOrder::GetTotalCost() {
    return total_cost;
}


