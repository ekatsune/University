#include "Cleaner.hpp"
#include <iostream>
/**
 * @file Cleaner.cpp
 * @brief Реализация класса `Cleaner`.
 * @details
 * Этот файл содержит реализацию методов класса `Cleaner`,
 * который моделирует уборку мусора.
 * @author
 * Ekatsune
 */
void Cleaner::GarbageRemoval() {
    garbage_bags++;

    if (garbage_bags >= 3) {
        std::cout << GetName() << " вынес полный мешок мусора.\n";
        garbage_bags = 0;
    } else {
        std::cout << GetName() << " собирает мусор. Мешок наполнен на "
                  << garbage_bags << "/3.\n";
    }
}

void Cleaner::Cleaning(WorkSchedule::Day day) {
    CleaningSchedule::CleaningType task = cleaningSchedule.GetTask(day);

    switch (task) {
        case CleaningSchedule::CleaningType::Wet:
            std::cout << GetName() << " проводит влажную уборку.\n";
            break;
        case CleaningSchedule::CleaningType::Dry:
            std::cout << GetName() << " делает сухую уборку.\n";
            break;
        case CleaningSchedule::CleaningType::Garbage:
            GarbageRemoval();
            break;
        case CleaningSchedule::CleaningType::Full:
            std::cout << GetName() << " делает генеральную уборку!\n";
            GarbageRemoval();
            break;
        default:
            std::cout << GetName() << " сегодня не убирается.\n";
    }
}

const CleaningSchedule& Cleaner::GetCleaningSchedule() const { return cleaningSchedule; }

CleaningSchedule& Cleaner::GetCleaningSchedule() { return cleaningSchedule; }

