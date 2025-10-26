/**
 * @file main.cpp
 * @brief Запуск работы машины Поста.
 * @details
 * Этот файл содержит функции `main(int argc, char* argv[])` и вспомогательную функцию `showMenu()`, которая выводит текстовое меню
 * программы.
 *
 * Если пользователь запустит программу из терминала с аргументом - именем текстового файла,
 * содержащего правила и ленту, а также с параметром `--log`, то программа выполнит правила из файла.
 * Если аргументы не будут указаны, пользователю будет предложено меню.
 * Он может ввести значения правил и ленту, редактировать правила и ленту, просмотреть список текущих установленных правил,
 * просмотреть текущее состояние ленты, запустить программу.
 *
 * @author Ekatsune
 * @see Machine
 */

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Machine.hpp"
using namespace std;

/**
 * @brief Текстовый вывод меню.
 */

void showMenu() {
    cout << "\n===== МЕНЮ МАШИНЫ =====\n";
    cout << "1. Ввести значения правил и ленту\n";
    cout << "2. Редактирование\n";
    cout << "3. Лист существующих правил\n";
    cout << "4. Текущее состояние ленты\n";
    cout << "5. Запуск программы\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

/**
 * @brief Точка входа в программу.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return Целое число — код завершения программы (0 при успешном завершении).
 * @see Machine
 */

int main(int argc, char* argv[]) {
    Machine machine;

    if (argc >= 2) {
        string filename = argv[1];
        bool logging = false;

        if (argc >= 3 && string(argv[2]) == "--log") {
            logging = true;
        }

        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Ошибка: не удалось открыть файл " << filename << endl;
            return 1;
        }

        machine.LoadProgram(fin);
        machine.LoadTape(fin);

        cout << "Программа загружена из " << filename << ".\n";
        machine.Run();

        return 0;
    }

    bool running = true;

    while (running) {
        showMenu();

        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1: {

                cout << "=============================================\n";
                cout << "\n=== Ввод программы ===\n";
                cout << "Формат:\n";
                cout << "  Для обычных действий: rule number  action  next rule\n";
                cout << "  Для условного перехода (moveIf): rule number  action  condition  next if zero  next if one\n";
                cout << "---------------------------------------------\n";
                cout << " Коды действий:\n";
                cout << "   1 — WRITE 1      (записать 1)\n";
                cout << "   2 — WRITE 0      (записать 0)\n";
                cout << "   3 — MOVE LEFT    (сдвинуться влево)\n";
                cout << "   4 — MOVE RIGHT   (сдвинуться вправо)\n";
                cout << "   5 — IF cond→rule (проверить символ и перейти)\n";
                cout << "   6 — END          (завершить выполнение)\n";
                cout << "---------------------------------------------\n";
                cout << "Введите правила по одному на строку.\n";
                cout << "Чтобы закончить ввод, оставьте строку пустой и нажмите Enter.\n";
                cout << "=============================================\n";

                machine.InputProgramFromConsole();
                machine.InputTapeFromConsole();
                break;
            }
            case 2: {
                bool secondRunning = true;
                int choose;
                while (secondRunning) {
                    cout << "МЕНЮ РЕДАКТОРА\n";
                    cout << "1. Удалить правило\n";
                    cout << "2. Добавить правило\n";
                    cout << "3. Изменить ленту\n";
                    cout << "0. Выйти\n";
                    cout << "Ваш выбор: ";
                    cin >> choose;
                    switch (choose) {
                        case 1: {
                            int ruleNumber;
                            machine.ShowRules();
                            cout << "Введите номер правила, который хотите удалить: ";
                            cin >> ruleNumber;
                            machine.RemoveRule(ruleNumber);
                        }
                        break;
                        case 2: {
                            int ruleNumber, actionInt;
                            cout << "Введите номер и действие (через пробел): ";
                            cin >> ruleNumber >> actionInt;

                            Rule::Ruls action = static_cast<Rule::Ruls>(actionInt);

                            if (action == Rule::moveIf) {
                                int condition, nextIfZero, nextIfOne;
                                cout << "Введите условие (0 или 1) и два перехода (если 0, если 1): ";
                                cin >> condition >> nextIfZero >> nextIfOne;

                                Rule rule(ruleNumber, action, condition, nextIfZero, nextIfOne);
                                machine.AddRule(rule);

                                cout << "Условное правило #" << rule.GetRuleNumber()
                                     << " успешно добавлено/обновлено.\n";
                            }
                            else {
                                int nextRule;
                                cout << "Введите номер следующего правила: ";
                                cin >> nextRule;

                                Rule rule(ruleNumber, action, nextRule);
                                machine.AddRule(rule);

                                cout << "Правило #" << rule.GetRuleNumber()
                                     << " успешно добавлено/обновлено.\n";
                            }
                            break;
                        }

                        case 3:{
                            int pos;
                            char val;
                            machine.ShowState();

                            cout << "\nВведите позицию для изменения: ";
                            cin >> pos;

                            cout << "Введите новое значение (0 или 1): ";
                            cin >> val;

                            try {
                                machine.GetTapeToModify(pos, val);
                                cout << "Лента изменена: позиция " << pos << " = " << val << "\n";
                            }
                            catch (const std::invalid_argument& e) {
                                cout << "Ошибка: " << e.what() << "\n";
                            }
                            break;
                        }
                        case 0:
                            secondRunning = false;
                            break;
                        default: cout << " Не корректный ввод, попробуйте ещё раз.\n"; break;
                    }
                }
                break;
            }
            case 3:
                machine.ShowRules();
                break;
            case 4:
                machine.ShowState();
                break;
            case 5:
                machine.Run();
                break;
            case 0:
                running = false;
                cout << "Выход . . .\n";
                break;

            default:
                cout << "Не корректный ввод!\n";
                break;
        }
    }

    return 0;
}
