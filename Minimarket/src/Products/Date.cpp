#include <iostream>
#include "Date.hpp"
#include <iomanip>
/**
 * @file Date.cpp
 * @brief Реализация класса `Date`.
 * @details
 * Этот файл содержит реализацию методов класса `Date`,
 * который моделирует формат даты.
 * @author
 * Ekatsune
 */

void Date::SetMinutes(int minutes) {
    if (minutes >= 0 && minutes < 60) this->minutes = minutes;
    else std::cerr << "Invalid minutes\n";
}

void Date::SetHours(int hours) {
    if (hours >= 0 && hours < 24) this->hours = hours;
    else std::cerr << "Invalid hours\n";
}

void Date::SetDays(int day) {
    if (day >= 1 && day <= 31) this->day = day;
    else std::cerr << "Invalid day\n";
}

void Date::SetMonth(int month) {
    if (month >= 1 && month <= 12) this->month = month;
    else std::cerr << "Invalid month\n";
}

void Date::SetYear(int year) {
    if (year > 0) this->year = year;
    else std::cerr << "Invalid year\n";
}

std::istream& operator>>(std::istream& is, Date& d) {
    int day, month, year;

    if (!(is >> day >> month >> year)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    d.SetDays(day);
    d.SetMonth(month);
    d.SetYear(year);

    return is;
}


std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << (d.day < 10 ? "0" : "") << d.day << "."
       << (d.month < 10 ? "0" : "") << d.month << "."
       << d.year << " "
       << (d.hours < 10 ? "0" : "") << d.hours << ":"
       << (d.minutes < 10 ? "0" : "") << d.minutes;

    return os;
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day &&
           hours == other.hours && minutes == other.minutes;
}

bool Date::operator!=(const Date& other) const {
    return !(*this == other);
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hours != other.hours) return hours < other.hours;
    return minutes < other.minutes;
}

bool Date::operator>(const Date& other) const { return other < *this; }

bool Date::operator<=(const Date& other) const { return !(*this > other); }

bool Date::operator>=(const Date& other) const { return !(*this < other); }