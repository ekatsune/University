#ifndef MINIMARKET_CLEANINGSCHEDULE_HPP
#define MINIMARKET_CLEANINGSCHEDULE_HPP

#include "WorkSchedule.hpp"

/**
 * @class CleaningSchedule
 * @brief Класс графика уборки
 * Наследует WorkSchedule и хранит задачи уборки по дням недели.
 * @see WorkSchedule
 */
class CleaningSchedule : public WorkSchedule {
public:
    /**
     * @brief Тип уборки
     */
    enum class CleaningType {
        None,    /**< Без уборки */
        Wet,     /**< Влажная уборка */
        Dry,     /**< Сухая уборка */
        Garbage, /**< Вынос мусора */
        Full     /**< Полная уборка */
    };

private:
    CleaningType tasks[7];  /**< Тип уборки по каждому дню недели (0=Пн, 6=Вс) */

public:
    /** @brief Конструктор, инициализирует все дни как None */
    CleaningSchedule();

    /**
     * @brief Установить задачу уборки на конкретный день
     * @param day День недели
     * @param type Тип уборки
     */
    void SetTask(Day day, CleaningType type);

    /**
     * @brief Получить задачу уборки на конкретный день
     * @param day День недели
     * @return CleaningType Тип уборки
     */
    CleaningType GetTask(Day day) const;

    /**
     * @brief Печать графика уборки
     */
    void PrintCleaning() const;
};

#endif //MINIMARKET_CLEANINGSCHEDULE_HPP
