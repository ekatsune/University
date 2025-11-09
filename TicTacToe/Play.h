#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

/**
 * @class Play
 * @brief Класс, реализующий логику игры "Крестики-нолики".
 */

class Play {
public:
 /** @brief Конструктор класса Play. */
 explicit Play (int size_of_field = 3);
 /** @brief Отрисовывает текущее состояние игрового поля. */
 void Draw ();
 /** @brief Выполняет ход игрока и обновляет игровое поле. */
 void Logic();
 /** @brief Проверяет, закончилась ли игра. */
 bool GetGameOver() const;
 /** @brief Проверяет, выполнены ли условия для победы/ничьи. */
 void AreWin();
 /** @brief Получение ссылки на элемент игрового поля. */
 vector<char>& operator[](int index);
 /** @brief Получение значения элемента игрового поля. */
 const vector<char>& operator[](int index) const;

private:
/** @brief Символ пустой клетки. */
static constexpr char empty_field = '*';
/** @brief Флаг окончания игры. */
 bool game_over = false;
 /** @brief Размер игрового поля. */
 int size;
 /** @brief Счетчик ходов (для проверки ничьи). */
 int move_count;
 /** @brief Двумерный вектор, представляющий игровое поле. */
 vector<vector <char>> field;
 /** @brief Отрисовывает заголовок с номерами столбцов. */
 void DrawHeader () const;
 /** @brief Отрисовывает строку игрового поля. */
 void DrawRow(int count);
 /** @brief Отрисовывает горизонтальные разделители между строками. */
 void DrawSeparator () const;
 /** @brief Проверяет все строки на наличие победителя. */
 bool CheckRows(char& winner);
 /** @brief Проверяет все столбцы на наличие победителя. */
 bool CheckCols(char& winner);
 /** @brief Проверяет диагонали на наличие победителя. */
 bool CheckDiagonals(char& winner);
 /** @brief Проверяет, наступила ли ничья. */
 bool CheckDraw();
};

