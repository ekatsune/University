#include "CleaningSchedule.hpp"
#include <iostream>
/**
 * @file CleaningSchedule.cpp
 * @brief Реализация класса `CleaningSchedule`.
 * @details
 * Этот файл содержит реализацию методов класса `CleaningSchedule`,
 * который моделирует расписание уборки и выноса мусора.
 * @author
 * Ekatsune
 */
CleaningSchedule::CleaningSchedule() {
    for (auto& t : tasks)
        t = CleaningType::None;
}

void CleaningSchedule::SetTask(Day day, CleaningType type) {
    tasks[static_cast<int>(day)] = type;
}

CleaningSchedule::CleaningType CleaningSchedule::GetTask(Day day) const {
    return tasks[static_cast<int>(day)];
}

void CleaningSchedule::PrintCleaning() const {
    static const char* names[] = {
            "нет уборки",
            "влажная уборка",
            "сухая уборка",
            "вынос мусора",
            "генеральная уборка"
    };

    std::cout << "\n=== График уборки ===\n";
    for (int i = 0; i < (int)Day::Count; i++) {
        Day d = (Day)i;

        std::cout << WorkSchedule::DayToString(d)
                  << ": " << names[(int)tasks[i]]
                  << " (рабочие часы: " << GetDay(d) << ")\n";
    }
    std::cout << "======================\n\n";
}
