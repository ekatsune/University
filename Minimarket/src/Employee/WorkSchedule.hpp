#ifndef MINIMARKET_WORKSCHEDULE_HPP
#define MINIMARKET_WORKSCHEDULE_HPP

#include <string>
#include <array>

/**
 * @class WorkSchedule
 * @brief Класс графика работы
 * Управляет рабочими часами для каждого дня недели и предоставляет методы их получения и вывода.
 * @see WorkSchedule
 */
class WorkSchedule {
public:
    /**
     * @brief День недели
     */
    enum class Day {
        Monday = 0,   /**< Понедельник */
        Tuesday,      /**< Вторник */
        Wednesday,    /**< Среда */
        Thursday,     /**< Четверг */
        Friday,       /**< Пятница */
        Saturday,     /**< Суббота */
        Sunday,       /**< Воскресенье */
        Count         /**< Служебное значение для размера массива */
    };

private:
    std::array<std::string, static_cast<int>(Day::Count)> schedule; /**< График работы по дням недели */

public:
    /** @brief Конструктор, инициализирует все дни пустыми строками */
    WorkSchedule(){
        for (auto& dayHours : schedule) {
        dayHours = "Не указано";
    }
};

    /**
     * @brief Установить рабочие часы для конкретного дня
     * @param day День недели
     * @param hours Строка с часами работы (например "09:00-18:00")
     */
    void SetDay(Day day, const std::string& hours);

    /**
     * @brief Получить рабочие часы конкретного дня
     * @param day День недели
     * @return std::string Часы работы
     */
    std::string GetDay(Day day) const;

    /**
     * @brief Вывести график работы на консоль
     */
    void Print() const;

    /**
     * @brief Преобразовать значение Day в строку
     * @param day День недели
     * @return std::string Название дня недели
     */
    static std::string DayToString(Day day);
};

#endif //MINIMARKET_WORKSCHEDULE_HPP
