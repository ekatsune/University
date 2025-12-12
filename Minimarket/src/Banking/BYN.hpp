#pragma once
#include <iostream>
/**
 * @class BYN
 * @brief Класс реализующий модель белорусской валюты.
 */
class BYN {
private:
    long long kopecks; /**< Количество копеек */

public:
    /**
     * @brief Конструктор по умолчанию, сумма = 0
     */
    BYN() : kopecks(0) {};

    /**
     * @brief Конструктор из общего количества копеек
     * @param total_kopecks Количество копеек
     */
    BYN(long long total_kopecks)
            : kopecks(total_kopecks) {};

    /**
     * @brief Конструктор из рублей и копеек
     * @param rubles Количество рублей
     * @param kopecks Количество копеек
     */
    BYN(long long rubles, long long kopecks)
            : kopecks(rubles * 100 + kopecks) {};

    /**
     * @brief Получить количество рублей
     * @return long long Рубли
     */
    long long GetRubles() const;

    /**
    * @brief Получить количество копеек
    * @return long long Копейки
    */
    long long GetKopecks() const;

    /**
     * @brief Создать BYN только из рублей
     * @param rubles Количество рублей
     * @return BYN Объект BYN
     */
    static BYN FromRubles(long long rubles) { return BYN(rubles, 0); }
    /**
    * @brief Ввод суммы в BYN из потока.
    *
    * Читает строку, заменяет запятую на точку и преобразует в копейки.
    * @param is Входной поток
    *  @param byn Объект BYN для записи значения
    * @return std::istream& Ссылка на входной поток
    */
    friend std::istream& operator>>(std::istream& is, BYN& b);
    /**
    * @brief Вывод суммы BYN в поток
    *
    * Формат: <рубли>,<копейки> BYN
    * @param os Выходной поток
    * @param byn Объект BYN
    * @return std::ostream& Ссылка на поток
    */
    friend std::ostream& operator<<(std::ostream& os, const BYN& b);

    /**
     * @brief Сложение BYN с возвратом нового объекта
     */
    BYN operator+(const BYN& other) const;

    /**
    * @brief Вычитание BYN с возвратом нового объекта
    */
    BYN operator-(const BYN& other) const;

    /**
    * @brief Сложение BYN с присваиванием
    */
    BYN& operator+=(const BYN& other);

    /**
    * @brief Вычитание BYN с присваиванием
    */
    BYN& operator-=(const BYN& other);

    /**
    * @brief Оператор "меньше" для BYN
    */
    bool operator<(const BYN& other) const;

    /**
    * @brief Оператор "больше" для BYN
    */
    bool operator>(const BYN& other) const;

    /**
    * @brief Оператор "меньше или равно" для BYN
    */
    bool operator<=(const BYN& other) const;

    /**
    * @brief Оператор "больше или равно" для BYN
    */
    bool operator>=(const BYN& other) const;

    /**
    * @brief Оператор "равно" для BYN
    */
    bool operator==(const BYN& other) const;

    /**
    * @brief Оператор "не равно" для BYN
    */
    bool operator!=(const BYN& other) const;

    /**
    * @brief Умножение BYN на число
    * @param value Множитель
    * @return BYN Результат умножения
    */
    BYN operator*(double value) const;

    /**
     * @brief Деление BYN на число
     * @param value Делитель
     * @return BYN Результат
     */
    BYN operator/(double value) const;
};




