#pragma once
#include <iostream>

/**
 * @class Date
 * @brief Класс для работы с датой и временем
 * Содержит день, месяц, год, часы и минуты, а также перегруженные операторы сравнения и ввода/вывода.
 */
class Date {
private:
    int minutes; /**< Минуты */
    int hours;   /**< Часы */
    int day;     /**< День */
    int month;   /**< Месяц */
    int year;    /**< Год */

public:
    /** @brief Конструктор по умолчанию (инициализирует текущей датой и временем) */
    Date() {
        time_t t = time(nullptr);
        tm* now = localtime(&t);
        minutes = now->tm_min;
        hours = now->tm_hour;
        day = now->tm_mday;
        month = now->tm_mon + 1;  // tm_mon: 0-11
        year = now->tm_year + 1900; // tm_year: с 1900
    }

    /**
     * @brief Конструктор с указанием даты
     * @param day День
     * @param month Месяц
     * @param year Год
     */
    Date(int day, int month, int year) : day(day), month(month),
    year(year), hours(0), minutes(0) {}

    /**
     * @brief Установить минуты
     * @param minutes Минуты
     */
    void SetMinutes(int minutes);

    /**
     * @brief Установить часы
     * @param hours Часы
     */
    void SetHours(int hours);

    /**
     * @brief Установить день
     * @param day День
     */
    void SetDays(int day);

    /**
     * @brief Установить месяц
     * @param month Месяц
     */
    void SetMonth(int month);

    /**
     * @brief Установить год
     * @param year Год
     */
    void SetYear(int year);

    /**
     * @brief Перегрузка оператора ввода
     * @param is Поток ввода
     * @param date Объект Date для чтения
     * @return std::istream& Поток ввода
     */
    friend std::istream& operator>>(std::istream& is, Date& date);

    /**
     * @brief Перегрузка оператора вывода
     * @param os Поток вывода
     * @param date Объект Date для записи
     * @return std::ostream& Поток вывода
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

    /** @brief Сравнение на равенство */
    bool operator==(const Date& other) const;

    /** @brief Сравнение на неравенство */
    bool operator!=(const Date& other) const;

    /** @brief Меньше */
    bool operator<(const Date& other) const;

    /** @brief Больше */
    bool operator>(const Date& other) const;

    /** @brief Меньше или равно */
    bool operator<=(const Date& other) const;

    /** @brief Больше или равно */
    bool operator>=(const Date& other) const;
};
