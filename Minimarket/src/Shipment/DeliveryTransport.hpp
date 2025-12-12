//
// Created by ekatsune on 30.11.2025.
//

#ifndef MINIMARKET_DELIVERYTRANSPORT_HPP
#define MINIMARKET_DELIVERYTRANSPORT_HPP

#include <iostream>
#include <string>

/**
 * @class DeliveryTransport
 * @brief Класс транспортного средства для доставки
 * Управляет характеристиками транспорта, загрузкой, доступностью и пробегом.
 */
class DeliveryTransport {
private:
    std::string model;          /**< Модель транспорта */
    std::string license_plate;  /**< Номерной знак */
    double mileage = 0.0;       /**< Пробег в километрах */
    double current_load_kg = 0.0; /**< Текущая загрузка в кг */
    double max_load_kg;         /**< Максимальная грузоподъёмность в кг */
    bool is_available = true;   /**< Флаг доступности для доставки */

public:
    /**
     * @brief Конструктор транспортного средства
     * @param model_name Модель
     * @param plate Номерной знак
     * @param load Максимальная грузоподъёмность
     */
    DeliveryTransport(const std::string& model_name,
                      const std::string& plate,
                      double load)
            : model(model_name),
              license_plate(plate),
              max_load_kg(load) {}

    /** @brief Проверка доступности транспорта */
    bool IsAvailable() const;

    /** @brief Получить модель транспорта */
    const std::string& GetModel() const;

    /** @brief Получить номерной знак */
    const std::string& GetLicensePlate() const;

    /** @brief Получить максимальную грузоподъёмность */
    double GetMaxLoad() const;

    /**
     * @brief Загрузить груз
     * @param weight Вес груза в кг
     * @return true если груз успешно загружен, иначе false
     */
    bool LoadCargo(double weight);

    /** @brief Разгрузить транспорт */
    void UnloadCargo();

    /** @brief Начать поездку */
    bool StartTrip();

    /**
     * @brief Завершить поездку и обновить пробег
     * @param distance_km Пройденное расстояние в км
     */
    void EndTrip(double distance_km);
};

#endif //MINIMARKET_DELIVERYTRANSPORT_HPP
