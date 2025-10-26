/**
 * @file Tape.cpp
 * @brief Реализация класса `Tape`.
 * @details
 * Этот файл содержит реализацию конструктора и методов класса `Tape`.
 * Реализованы методы: `Tape ()`, `int Read()`, `void WriteOne()`, `void WriteZero()`, `void MoveRight()`;
 * `void MoveLeft()`, `void ShowTape()`, `void ModifyTape(int positionT, char value)`,
 * а также перегрузка оператора `operator>>`.
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
 */

int Tape::GetSymbol(int positionT) {
    if (tape.find(positionT) != tape.end()) {
        return tape[positionT];
    }
    return zero;
}

/**
 * @brief  Сеттер символа.
 * @details
 *  По переданному значению позиции в ленте `positionT` и значению ячейки ленты `symbol`
 *  ставит на указанную позицию нужный символ.
 */

void Tape::SetSymbol(int positionT, int symbol) {
    tape[positionT] = symbol;
}

/**
 * @brief  Чтение текущего символа.
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
 * @brief  Перегрузка оператора 'operator>>'.
 * @details Оператор ввода перегружается таким образом, чтобы можно было вводить значения ячеек
 * ленты более понятной записью.
 */

std::istream& operator>>(std::istream& in, Tape& t) {
    std::string s;

    while (std::getline(in, s)) {
        while (!s.empty() && (s.back() == '\r' || s.back() == ' ' || s.back() == '\t'))
            s.pop_back();

        if (!s.empty()) break;
    }

    if (s.empty()) return in;
    t.tape.clear();
    t.position = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '0')
            t.tape[(int)i] = 0;
        else if (s[i] == '1')
            t.tape[(int)i] = 1;
    }

    return in;
}

/**
 * @brief Редактирование ленты.
 *  * @details
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
