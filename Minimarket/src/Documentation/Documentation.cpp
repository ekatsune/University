#include "Documentation.hpp"
#include <iostream>
/**
 * @file Documentation.cpp
 * @brief Реализация класса `Documentation`.
 * @details
 * Этот файл содержит реализацию методов класса `Documentation`,
 * который моделирует ведение документации в минимаркете.
 * @author
 * Ekatsune
 */
std::string Documentation::GetCurrentDateTime() const {
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", local);
    return std::string(buffer);
}

void Documentation::AddDocument(const std::string& title,
                                const std::string& content) {
    documents.emplace_back(title, content);
}

void Documentation::CollectCashReport(Cashier& cashier) {
    std::string report = cashier.CashReportText();  // получаем текст отчёта
    std::string title = "Кассовый отчёт " + GetCurrentDateTime();
    documents.emplace_back(title, report);
}

void Documentation::CollectWarehouseBalanceReport(const WarehouseWorker& worker) {
    std::string title = "Складской отчёт (" + GetCurrentDateTime() + ")";
    const auto& products = worker.GetWarehouseState();
    std::string content =
            "Отчёт предоставил работник склада: "
            + worker.GetName() + " " + worker.GetSurname() + "\n";
    content += "Количество позиций на складе: "
               + std::to_string(products.size()) + "\n\n";
    if (products.empty()) {
        content += "Склад пуст.\n";
        documents.emplace_back(title, content);
        return;
    }
    for (const auto& p : products) {
        content += "- " + p.GetName()
                   + " | цена: " + std::to_string(p.GetPrice().GetRubles())
                   + " BYN | кол-во: " + std::to_string(p.GetQuantity())
                   + "\n";
    }
    documents.emplace_back(title, content);
}

void Documentation::PrintAll() const {
    if (documents.empty()) {
        std::cout << "Документов нет.\n";
        return;
    }

    int index = 0;
    for (const auto& d : documents) {
        std::cout << "\n==== ДОКУМЕНТ #" << index++ << " ====\n";
        std::cout << "Название: " << d.first << "\n";
        std::cout << d.second << "\n";
    }
}

void Documentation::PrintDocument(int index) const {
    if (index < 0 || index >= (int)documents.size()) {
        std::cout << "Некорректный индекс!\n";
        return;
    }

    std::cout << "\n==== ДОКУМЕНТ #" << index << " ====\n";
    std::cout << "Название: " << documents[index].first << "\n";
    std::cout << documents[index].second << "\n";
}

const std::vector<std::pair<std::string, std::string>>&
Documentation::GetAllDocuments() const { return documents; }

