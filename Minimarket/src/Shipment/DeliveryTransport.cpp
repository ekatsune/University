#include "DeliveryTransport.hpp"
/**
 * @file DeliveryTransport.cpp
 * @brief Реализация класса `DeliveryTransport`.
 * @details
 * Этот файл содержит реализацию методов класса `DeliveryTransport`,
 * который моделирует состояния транспорта доставки и содержит информацию о нём.
 * @author
 * Ekatsune
 */
bool DeliveryTransport::IsAvailable() const { return is_available; }

const std::string& DeliveryTransport::GetModel() const { return model; }

const std::string& DeliveryTransport::GetLicensePlate() const { return license_plate; }

double DeliveryTransport::GetMaxLoad() const { return max_load_kg; }

bool DeliveryTransport::LoadCargo(double weight) {
    if (current_load_kg + weight > max_load_kg) {
        std::cout << "Превышение допустимой нагрузки! Загрузка невозможна.\n";
        return false;
    }
    current_load_kg += weight;
    return true;
}

void DeliveryTransport::UnloadCargo() {
    current_load_kg = 0;
}

bool DeliveryTransport::StartTrip() {
    if (!is_available) {
        std::cout << "Транспорт уже в пути!\n";
        return false;
    }
    is_available = false;
    std::cout << "Транспорт выехал." << "\n";
    return true;
}

void DeliveryTransport::EndTrip(double distance_km) {
    is_available = true;
    mileage += distance_km;
    std::cout << "Поездка завершена. Пробег +" << distance_km << "\n";
}

