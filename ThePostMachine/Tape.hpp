#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <istream>
using namespace std;
/**
 * @class Tape
 * @brief Класс реализующий работу с лентой и кареткой.
 */
class Tape {
private:
/** @brief Перечисление корректных символов ленты. */
    enum Symbol {zero, one};
    /** @brief Текущая позиция каретки. */
    int position = 0;
    /** @brief Хранение ленты. */
    map <int,int> tape;
    /** @brief Геттер значения под кореткой. */
    int GetSymbol (int positionT);
    /** @brief Сеттер значения под каретку. */
    void SetSymbol (int positionT, int symbol);
public:
    /** @brief Конструктор класса. */
    Tape ();
    /** @brief Чтение символа в текущем состоянии каретки. */
    int Read();
    /** @brief Установка `1` в текущую ячейку ленты. */
    void WriteOne();
    /** @brief Установка `0` в текущую ячейку ленты. */
    void WriteZero();
    /** @brief Движение каретки вправо. */
    void MoveRight();
    /** @brief Движение каретки влево. */
    void MoveLeft();
    /** @brief Просмотр состояния всей ленты. */
    void ShowTape();
    /** @brief Редактирование значений на ленте. */
    void ModifyTape(int positionT, char value);
    /** @brief Перегрузка оператора ввода. */
    friend std::istream& operator>>(std::istream& in, Tape& t);
};

