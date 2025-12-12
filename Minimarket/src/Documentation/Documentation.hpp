//
// Created by ekatsune on 30.11.2025.
//

#ifndef MINIMARKET_DOCUMENTATION_HPP
#define MINIMARKET_DOCUMENTATION_HPP

#include "../Employee/WarehouseWorker.hpp"
#include "../Employee/Cashier.hpp"
#include <vector>
#include <string>

/**
 * @class Documentation
 * @brief Класс для ведения документации магазина
 * Управляет различными документами, включая отчёты кассиров и складских работников.
 */
class Documentation {
private:
    std::vector<std::pair<std::string, std::string>> documents; /**< Список документов (название, текст) */

    /**
     * @brief Получить текущие дату и время
     * @return std::string Текущие дата и время в строковом формате
     */
    std::string GetCurrentDateTime() const;

public:
    /** @brief Конструктор по умолчанию */
    Documentation() = default;

    /**
     * @brief Добавить произвольный документ
     * @param title Название документа
     * @param content Содержание документа
     */
    void AddDocument(const std::string& title,
                     const std::string& content);

    /**
     * @brief Запрос у кассира на предоставление отчёта
     * @param cashier Ссылка на кассира
     */
    void CollectCashReport(Cashier& cashier);

    /**
     * @brief Запрос у складского работника отчёта об остатках
     * @param worker Ссылка на складского работника
     */
    void CollectWarehouseBalanceReport(const WarehouseWorker& worker);

    /**
     * @brief Получить полный список документов
     * @return const std::vector<std::pair<std::string, std::string>>& Список документов
     */
    const std::vector<std::pair<std::string, std::string>>& GetAllDocuments() const;

    /**
     * @brief Печать всех документов
     */
    void PrintAll() const;

    /**
     * @brief Печать конкретного документа
     * @param index Индекс документа в списке
     */
    void PrintDocument(int index) const;
};

#endif //MINIMARKET_DOCUMENTATION_HPP
