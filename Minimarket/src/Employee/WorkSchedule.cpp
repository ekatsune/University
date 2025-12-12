#include "WorkSchedule.hpp"
#include <iostream>
/**
 * @file WorkSchedule.cpp
 * @brief Реализация класса `WorkSchedule`.
 * @details
 * Этот файл содержит реализацию методов класса `WorkSchedule`,
 * который моделирует общее расписание работы сотрудников.
 * @author
 * Ekatsune
 */
void WorkSchedule::SetDay(Day day, const std::string& hours) {
    schedule[static_cast<int>(day)] = hours;
}

std::string WorkSchedule::GetDay(Day day) const {
    return schedule[static_cast<int>(day)];
}

std::string WorkSchedule::DayToString(Day day) {
    switch (day) {
        case Day::Monday:    return "Понедельник";
        case Day::Tuesday:   return "Вторник";
        case Day::Wednesday: return "Среда";
        case Day::Thursday:  return "Четверг";
        case Day::Friday:    return "Пятница";
        case Day::Saturday:  return "Суббота";
        case Day::Sunday:    return "Воскресенье";
        default:             return "Неизвестный день";
    }
}

void WorkSchedule::Print() const {
    std::cout << "\n=== График работы ===\n";
    for (int i = 0; i < static_cast<int>(Day::Count); i++) {
        Day d = static_cast<Day>(i);
        std::cout << DayToString(d) << ": " << schedule[i] << "\n";
    }
    std::cout << "=====================\n\n";
}
