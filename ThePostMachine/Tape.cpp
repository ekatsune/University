/**
 * @file Tape.cpp
 * @brief Реализация класса `Tape`.
 * @details
 * Этот файл содержит реализацию конструктора и методов класса `Tape`.
 * Реализованы методы:
 * - `Tape ()`
 * - `Tape::GetSymbol(int positionT)`
 * - `void SetSymbol(int positionT, int symbol)`
 * - `int Read()`
 * - `void WriteOne()`
 * - `void WriteZero()`
 * - `void MoveRight()`
 * - `void MoveLeft()`
 * - `void ShowTape()`
 * - `void ModifyTape(int positionT, char value)`
 * - перегрузка оператора `operator>>`.
 * @author Ekatsune
 * @see Tape
 */

#include "Tape.hpp"
#include <iostream>
#include <istream>

/**
 * @brief Конструктор класса.
 * @details
 * Создает ленту, инициализируя первую ячейку символом `0`.
 */

Tape::Tape() {
    tape[position] = zero;
}

/**
 * @brief Геттер символа.
 * @details
 * По переданному значению позиции в ленте `positionT` ищет и возвращает значение ленты на позиции.
 * Если такой позиции в ленте не задано, возвращает ноль (иммитация бесконечной ленты).
 * @param positionT - позиция в ленте, с которой нужно считать символ.
 * @return Символ (`0` или `1`) на заданной позиции.
 */

int Tape::GetSymbol(int positionT) {
    if (tape.find(positionT) != tape.end()) {
        return tape[positionT];
    }
    return zero;
}

/**
 * @brief  Сеттер символа.
 * @details Заменяет или добавляет значение символа в ленту `tape`.
 * @param positionT - позиция в ленте, которую требуется изменить.
 * @param symbol - значение ячейки (`0` или `1`).
 */

void Tape::SetSymbol(int positionT, int symbol) {
    tape[positionT] = symbol;
}

/**
 * @brief  Чтение текущего символа.
 * @return Символ (`0` или `1`), находящийся под кареткой.
 */

int Tape::Read() {
    return GetSymbol(position);
}

/**
 * @brief  Установка `1` в текущую ячейку ленты.
 */

void Tape::WriteOne() {
    SetSymbol(position, one);
}

/**
 * @brief  Установка `0` в текущую ячейку ленты.
 */

void Tape::WriteZero() {
    SetSymbol(position, zero);
}

/**
 * @brief  Увеличение позиции на 1 (сдвиг каретки вправо).
 */

void Tape::MoveRight() {
    position++;
}

/**
 * @brief  Уменьшение позиции на 1 (сдвиг каретки влево).
 */

void Tape::MoveLeft() {
    position--;
}

/**
 * @brief  Просмотр ленты.
 * @details Если лента пустая, метод выводит в консоль соответствующее сообщение. Если лента заполнена,
 * метод выводит её с указанием символа, на котором сейчас стоит каретка, в '[]'.
 */

void Tape::ShowTape() {
    if (tape.empty()) {
        std::cout << "(лента пуста)" << std::endl;
        return;
    }

    size_t start = 0;
    size_t end = tape.rbegin()->first;

    std::cout << "Tape: ";
    for (size_t i = start; i <= end; ++i) {
        if (i == position)
            std::cout << "[" << tape[i] << "] ";
        else
            std::cout << tape[i] << " ";
    }
    std::cout << std::endl;
}

/**
 * @brief Перегрузка оператора ввода `>>`.
 * @param input - входной поток (`std::istream`).
 * @param tape - объект ленты, в который будут считаны данные.
 * @return Ссылка на входной поток `input`.
 * @details
 * Считывает строку символов `0` и `1` и инициализирует ленту соответствующими значениями.
 *
 * Пример формата ввода:
 * ```
 * 0110101
 * ```
 */

std::istream& operator>>(std::istream& input, Tape& tape) {
    std::string string;

    while (std::getline(input, string)) {
        while (!string.empty() && (string.back() == '\r' || string.back() == ' ' || string.back() == '\t'))
            string.pop_back();

        if (!string.empty()) break;
    }

    if (string.empty()) return input;
    tape.tape.clear();
    tape.position = 0;

    for (size_t i = 0; i < string.size(); ++i) {
        if (string[i] == '0')
            tape.tape[(int)i] = 0;
        else if (string[i] == '1')
            tape.tape[(int)i] = 1;
    }

    return input;
}

/**
 * @brief Редактирование ленты.
 * @param positionT - позиция ячейки, значение которой требуется изменить.
 * @param value - новый символ (`'0'` или `'1'`).
 * @details
 * Изменяет символ на указанной позиции. Разрешены только символы `0` и `1`.
 * При вводе других значений выбрасывается исключение `std::invalid_argument`.
 */

void Tape::ModifyTape(int positionT, char value) {
    if (value != '0' && value != '1') {
        throw std::invalid_argument("На ленте можно записывать только '0' или '1'");
    }

    int symbol = (value == '0') ? zero : one;
    SetSymbol(positionT, symbol);
}
