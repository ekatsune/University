#include "Provider.hpp"
/**
 * @file PurchaseOrder.cpp
 * @brief Реализация класса `PurchaseOrder`.
 * @details
 * Этот файл содержит реализацию методов класса `PurchaseOrder`,
 * который моделирует Управляет информацией о компании-поставщике, заказами, доставкой и рейтингом надёжности.
 * @author
 * Ekatsune
 */
PurchaseOrder Provider::CreateOrder(const std::vector<Product>& products,
                                    const std::string& destination) const
{
    PurchaseOrder order{
            const_cast<Provider*>(this),
            products,
            destination
    };
    return order;
}

const std::string& Provider::GetName() const { return company_name; }

const std::string& Provider::GetPhone() const { return contact_phone; }

const std::string& Provider::GetEmail() const { return contact_email; }

bool Provider::IsAvailable() const { return !is_busy; }

ProductsDelivery Provider::StartDelivery(PurchaseOrder& order){
    if (!IsAvailable()) {
        std::cout << "Поставщик занят выполнением другого заказа!\n";
        orders_failed++;
        order.SetStatus(PurchaseOrder::Status::Rejected);
        return ProductsDelivery();
    }
    is_busy = true;
    order.SetStatus(PurchaseOrder::Status::InDelivery);
    DeliveryTransport transport("Mercedes Sprinter", "5555 AA-7", 1500);
    size_t id = supplies.size();
    ProductsDelivery delivery(order,transport);
    supplies.push_back(delivery);
    std::cout << "Поставка #" << id << " началась.\n";
    return delivery;
}

double Provider::CalculateReliability() const {
    if (orders_completed + orders_failed == 0) return 1.0;
    return static_cast<double>(orders_completed) /
           (orders_completed + orders_failed);
}

void Provider::AddProductCategory(const std::string& category) {
    product_categories.push_back(category);
}

const ProductsDelivery* Provider::TrackSupply(size_t supply_id) const{
    if (supply_id >= supplies.size())
        return nullptr;
    return &supplies[supply_id];
}

void Provider::FinishOrder(bool success) {
    is_busy = false;
    if (success) orders_completed++;
    else orders_failed++;
}
