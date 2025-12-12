//
// Created by ekatsune on 07.12.2025.
//

#ifndef MINIMARKET_SHKAF_HPP
#define MINIMARKET_SHKAF_HPP

#include "Shelf.hpp"
#include <vector>
#include <string>

/**
 * @class Shkaf
 * @brief Класс шкафа
 * Представляет шкаф с полками в магазине, хранит несколько полок и управляет ими.
 */
class Shkaf {
private:
    std::vector<Shelf*> shelves;       /**< Список полок в шкафу */
    std::string name;                   /**< Название шкафа */
    const int quantity_of_shelfs = 5;  /**< Максимальное количество полок */

public:
    /** @brief Конструктор по умолчанию */
    Shkaf() = default;

    /**
     * @brief Конструктор с указанием названия
     * @param name Название шкафа
     */
    explicit Shkaf(const std::string& name)
            : name(name) {}

    /** @brief Деструктор, удаляет все полки */
    ~Shkaf() {
        for (auto* shelf : shelves) {
            delete shelf;
        }
    }

    /**
     * @brief Добавить полку в шкаф
     * @param shelf Указатель на полку
     */
    void AddShelf(Shelf* shelf);

    /**
     * @brief Удалить полку по индексу
     * @param index Индекс полки
     */
    void RemoveShelf(int index);

    /**
     * @brief Получить полку по индексу
     * @param index Индекс полки
     * @return Shelf* Указатель на полку
     */
    Shelf* GetShelf(int index) const;

    /**
     * @brief Получить количество полок в шкафу
     * @return int Количество полок
     */
    int GetShelfCount() const;

    /**
     * @brief Показать все полки в шкафу
     */
    void ShowShelves() const;

    /**
     * @brief Получить название шкафа
     * @return const std::string& Название
     */
    const std::string& GetName() const;

    /**
     * @brief Установить название шкафа
     * @param sh_name Новое название
     */
    void SetName(const std::string& sh_name);
};

#endif //MINIMARKET_SHKAF_HPP
