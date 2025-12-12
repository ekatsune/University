#include "ProductsDelivery.hpp"
#include "PurchaseOrder.hpp"
/**
 * @file ProductsDelivery.cpp
 * @brief Реализация класса `ProductsDelivery`.
 * @details
 * Этот файл содержит реализацию методов класса `ProductsDelivery`,
 * который моделирует итоговый процесс доставки.
 * @author
 * Ekatsune
 */
void ProductsDelivery::MarkDelivered(ProductsInWarehouse& warehouse_products) {
    if (delivered) {
        std::cout << "Поставка уже была выполнена!\n";
        return;
    }
    double total_weight = 0.0;
    for (const auto& p : order->GetProducts()) {
        total_weight += p.GetWeight();
    }
    if (!transport.LoadCargo(total_weight)) {
        std::cout << "Невозможно выполнить доставку: превышение массы!\n";
        return;
    }
    transport.StartTrip(); transport.EndTrip(15.3); transport.UnloadCargo();
    for (const auto& product : order->GetProducts()) {
        warehouse_products.AddProductToListOfProd(product);
    }
    delivered = true;
    order->SetStatus(PurchaseOrder::Status::Delivered);
    std::cout << "Поставка успешно завершена!\n";
}

PurchaseOrder* ProductsDelivery::GetOrder() const { return order; }

const DeliveryTransport& ProductsDelivery::GetTransport() const { return transport; }

bool ProductsDelivery::IsDelivered() const { return delivered; }