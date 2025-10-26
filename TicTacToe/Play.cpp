/**
 * @file Play.cpp
 * @brief Реализация класса `Play`.
 * @details
 * Этот файл содержит реализацию конструктора и методов класса `Play`.
 * Реализованы методы: Draw(), Logic(), GetGameOver(), AreWin(),
 * DrawHeader(), DrawRow(), DrawSeparator(), CheckRows(), CheckCols(),
 * CheckDiagonals(), CheckDraw(), а также перегрузки операторов `operator[]`.
 * @author Ekatsune
 * @see Play
 */


#include <iostream>
#include "Play.h"

/**
 * @brief Конструктор класса.
 * @details
 * Создаёт поле размером `size_of_field`, если этот параметр < 1, то по умолчанию
 * создаёт поле 3*3. Заполняет всё символами пустого поля `*`. Счётчик ходов приравнивается нулю.
 * Флаг завершения игры - ложный.
 */

Play::Play(int size_of_field) {
    size = (size_of_field < 1 ? 3 : size_of_field);
    field.assign(size, vector<char>(size, empty_field));
    move_count = 0;
    game_over = false;
}

/**
 * @brief Отрисовка чисел вокруг поля.
 * @details
 * По имеющемуся значению размера поля красиво рисует шапку из чисел, на пересечении котрых
 * должны быть клетки.
 */

void Play::DrawHeader () const {
    std::cout << "   ";
    for (int i = 0; i< size; i++) {
        if(i>=9) std::cout << setw(5) << i+1;
        else std::cout << setw(3) << i + 1;
    }
    std::cout << endl;
}

/**
 * @brief Отрисовка разделителей между столбцами.
 * @details
 * По передающемуся значению рисует '|' между полями для разделения столбцов.
 */

void Play::DrawRow(int count) {std::cout << setw(3) << count + 1;
    for (int i = 0; i < size; i++) {
        std::cout << setw(3) << (*this)[count][i];
        if (i + 1 < size) std::cout << "|";
    }
    std::cout << "\n";
}

/**
 * @brief Отрисовка разделителей между строками.
 * @details
 * Рисует '---' для разделения строк и '+' для обозначения узлов сетки.
 */

void Play::DrawSeparator () const {
    std::cout << "   ";
    for (int i = 0; i < size; i++) {
        std::cout << "---";
        if (i + 1 < size) std::cout << "+";
    }
    std::cout << endl;
}

/**
 * @brief Отрисовка игрового поля.
 * @details
 * Вызывает функции отрисовки других частей поля, согласно заданному размеру.
 * @see DrawHeader(), DrawRow(), DrawSeparator()
 */

void Play::Draw() {
    DrawHeader();
    for (int i = 0; i < size; i++) {
        DrawRow(i);
        if (i + 1 < size) DrawSeparator();
    }
    std::cout << "\n";
}

/**
 * @brief Логика игры.
 * @details
 * Метод предусматривает решение очереди хода. Принимает значения координат для хода.
 * Производит проверки на корректность введённых данных:
 * 1) введённые значения не выходят за установленные границы;
 * 2) клетка не занята другим символом, кроме символа пустой клетки `empty_field`.
 * Выбранная пользователем клетка заполняется соответствующим символом (`0` или `X`).
 * Затем увеличивается счётчик ходов и проиходит проверка на условия выигрыша.
 */

void Play::Logic() {
    int row, column;
    char symbol = (move_count % 2 == 0 ? 'X' : 'O');

    std::cout << "Now play " << symbol << ". Enter the row and column: ";
    std::cout << "row: "; std::cin >> row;
    std::cout << "column: "; std::cin >> column;

    if (row < 1 || row > size || column < 1 || column > size) {
        std::cout << "Not correct!\n";
        return;
    }
    if ((*this)[row-1][column-1] != empty_field) {
        std::cout << "Field is occupied!\n";
        return;
    }
    (*this)[row - 1][column - 1] = symbol;
    move_count++;

    AreWin();
}

/**
 * @brief Просмотр строк.
 * @details
 * Метод проверяет: выполнено ли условие победы в строках? В данном случае:
 * собраны ли одинаковые символы в строках поля в количестве, равном его длине/ширине? В случае определения
 * чьей-то победы, полю класса `winner` присваивается значение выигравшего пользователя.
 * @return Булевое значение - выполнено/не выполнено условие победы (`true` - если да, `false` - если нет).
 */

bool Play::CheckRows(char& winner) {
    for (int row = 0; row < size; row++) {
        char first = (*this)[row][0];
        if (first == empty_field) continue;
        bool same = true;
        for (int column = 1; column < size; column++) {
            if ((*this)[row][column] != first) { same = false; break; }
        }
        if (same) {
            winner = first;
            return true;
        }
    }
    return false;
}

/**
 * @brief Просмотр столбцов.
 * @details
 * Метод проверяет: выполнено ли условие победы в столбцах? В данном случае:
 * собраны ли одинаковые символы в столбцах поля в количестве, равном его длине/ширине? В случае определения
 * чьей-то победы, полю класса `winner` присваивается значение выигравшего пользователя.
 * @return Булевое значение - выполнено/не выполнено условие победы (`true` - если да, `false` - если нет).
 */

bool Play::CheckCols(char& winner) {
    for (int column = 0; column < size; column++) {
        char first = (*this)[0][column];
        if (first == empty_field) continue;
        bool same = true;
        for (int row = 1; row < size; row++) {
            if ((*this)[row][column] != first) { same = false; break; }
        }
        if (same) {
            winner = first;
            return true;
        }
    }
    return false;
}

/**
 * @brief Просмотр диагоналей.
 * @details
 * Метод проверяет: выполнено ли условие победы в диагоналях? В данном случае:
 * собраны ли одинаковые символы в главной или побочной диагонали поля в количестве, равном его длине/ширине?
 * В случае определения чьей-то победы, полю класса `winner` присваивается значение выигравшего пользователя.
 * @return Булевое значение - выполнено/не выполнено условие победы (`true` - если да, `false` - если нет).
 */

bool Play::CheckDiagonals(char& winner) {
    char first = (*this)[0][0];
    if (first != empty_field) {
        bool same = true;
        for (int i = 1; i < size; i++) {
            if ((*this)[i][i] != first) { same = false; break; }
        }
        if (same) { winner = first; return true; }
    }
    first = (*this)[0][size - 1];

    if (first != empty_field) {
        bool same = true;
        for (int i = 1; i < size; i++) {
            if ((*this)[i][size - 1 - i] != first) { same = false; break; }
        }
        if (same) { winner = first; return true; }
    }

    return false;
}

/**
 * @brief Просмотр ничьи.
 * @details
 * Метод проверяет: выполнено ли условие ничьи? В данном случае:
 * остались ли на игровом поле пустые клетки?
 * @return Булевое значение - выполнено/не выполнено условие ничьи (`true` - если да, `false` - если нет).
 */

bool Play::CheckDraw() {
    for (int row = 0; row < size; ++row)
        for (int column = 0; column < size; ++column)
            if ((*this)[row][column] == empty_field)
                return false;
    return true;
}

/**
 * @brief Проверка победы.
 * @details
 * Метод комбинирует в себе вызов других методов для проверки условий победы/ничьи:
 * CheckRows(char& winner), CheckCols(char& winner), CheckDiagonals(char& winner),
 * CheckDraw(). Если какое-либо условие победы или ничьи срабатывает, то полю конца игры `game_over`
 * присвается значение `true`, в консоли отображается соответствующее сообщение. Если же никакой из методов не передал
 * значения `true` (никакое из условий для завершения игры не выполнилось), то игра продолжается.
 * @see CheckRows(char& winner), CheckCols(char& winner), CheckDiagonals(char& winner),
 * CheckDraw()
 */

void Play::AreWin() {
    char winner;

    if (CheckRows(winner) || CheckCols(winner) || CheckDiagonals(winner)) {
        Draw();
        std::cout << "Win " << winner << "!\n";
        game_over = true;
    }
    else if (CheckDraw()) {
        Draw();
        std::cout << "Draw!\n";
        game_over = true;
    }
    else game_over = false;
}

/**
 * @brief Геттер флага конца игры.
 * @details
 * Метод возвращает значение приватного поля `game_over`.
 * @return Булевое значение, зависящее от значения поля `game_over` (`true`/`false`).
 */

    bool Play::GetGameOver() const {
    return game_over;
}

/**
 * @brief Получение ссылки на элемент игрового поля.
 * @return Ссылка на элемент (символ) в указанной позиции.
 */

vector<char>& Play::operator[](int index)  {
        return field[index];
}

/**
 * @brief Получение значения элемента игрового поля.
 * @return Символ, находящийся в указанной позиции.
 */

const vector<char>& Play::operator[](int index) const  {
        return field[index];
}
