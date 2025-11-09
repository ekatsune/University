/**
 * @file Machine.cpp
 * @brief Реализация класса `Machine`.
 * @details
 * Этот файл содержит реализацию конструктора и методов класса `Machine`,
 * который моделирует работу машины Поста.
 * Реализованы методы:
 * - `Machine()`
 * - `void parseRuleLine(const std::string&)`
 * - `void parseSimpleRule(int, Rule::Ruls, std::istringstream&)`
 * - `void parseConditionalRule(int, Rule::Ruls, std::istringstream&, const std::string&)`
 * - `void LoadProgram(std::istream&)`
 * - `void LoadTape(std::istream&)`
 * - `void InputTapeFromConsole()`
 * - `void InputProgramFromConsole()`
 * - `int GetCurrentRule() const`
 * - `void AddRule(const Rule&)`
 * - `void RemoveRule(int)`
 * - `void ShowRules()`
 * - `void Step()`
 * - `void Run(bool log)`
 * - `void ShowState()`
 * - `void GetTapeToModify(int, char)`
 * @see Machine, Tape, Rule
 * @author
 * Ekatsune
 */

#include <istream>
#include "Machine.hpp"
#include "Tape.hpp"
#include "Rule.hpp"
#include <map>
#include <sstream>
#include <limits>
#include <iostream>
using namespace std;

/**
 * @brief Конструктор класса `Machine`.
 * @details
 * Инициализирует объект машины, устанавливая текущее правило в 1 (начальное состояние).
 */

Machine::Machine() : currentRule(1) {}

/**
 * @brief Разбор строки с правилом.
 * @details
 * Разделяет строку с текстовым описанием правила и создает объект `Rule`.
 *
 * @param line Строка, содержащая данные одного правила.
 */

void Machine::ParseRuleLine(const std::string& line) {
    std::istringstream ss(line);

    int ruleNumber, actionInt;
    if (!(ss >> ruleNumber >> actionInt)) {
        std::cerr << "Ошибка: пропущен номер или действие в строке: " << line << "\n";
        return;
    }

    Rule::Ruls action = static_cast<Rule::Ruls>(actionInt);

    if (action == Rule::moveIf)
        ParseConditionalRule(ruleNumber, action, ss, line);
    else
        ParseSimpleRule(ruleNumber, action, ss);
}

/**
 * @brief Разбиение строки на парметры не условного правила.
 * @details
 * Создаёт объект `Rule` без условия и добавляет его в коллекцию `rules`.
 * @param ruleNumber - параметр номера правила.
 * @param action - параметр дейтсвия правила
 * @param ss - поток с оставшимися параметрами строки.
 */

void Machine::ParseSimpleRule(int ruleNumber, Rule::Ruls action,
                              std::istringstream& ss) {
    int nextRule;

    if (!(ss >> nextRule)) {
        ss.clear();
        ss.seekg(0);
        int tmpAction;
        ss >> ruleNumber >> tmpAction >> nextRule;
    }

    rules[ruleNumber] = Rule(ruleNumber, action, nextRule);
}

/**
 * @brief Разбиение строки на парметры условного правила.
 * @details
 * Создает условное правило с проверкой символа и двумя переходами:
 * - `nextIfZero` — если символ равен 0;
 * - `nextIfOne` — иначе.
 * @param ruleNumber - параметр номера правила.
 * @param action - параметр дейтсвия правила
 * @param ss - поток с параметрами условия.
 * @param line - исходная строка.
 */

void Machine::ParseConditionalRule(int ruleNumber, Rule::Ruls action,
                                   std::istringstream& ss, const std::string& line) {
    int condition, nextIfZero, nextIfOne;

    if (!(ss >> condition >> nextIfZero >> nextIfOne)) {
        std::cerr << " Ошибка: некорректный формат условного правила:\n"
                  << "   " << line << "\n";
        return;
    }

    rules[ruleNumber] = Rule(ruleNumber, action, condition, nextIfZero, nextIfOne);
}

/**
 * @brief Загрузка программы из входного потока.
 * @details
 * Метод построчно читает правила до тех пор, пока не встретит строку,
 * состоящую только из `0` и `1` — она считается инициализацией ленты.
 * @param input - параметр входной потока с программой и лентой.
 */

void Machine::LoadProgram(std::istream& input) {
    rules.clear();
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) continue;
        if (line.find_first_not_of("01") == std::string::npos) {
            std::istringstream tapeStream(line);
            tapeStream >> tape;
            break;
        }
        ParseRuleLine(line);
    }

    input.clear();
    std::cout << "Программа успешно загружена (" << rules.size() << " правил).\n";
}

/**
 * @brief Инициализация ленты.
 * @param input - поток с описанием начального состояния ленты.
 */

void Machine::LoadTape(std::istream& input) {
    input >> tape;
}

/**
 * @brief Ввод ленты из консоли.
 * @details
 * Пользователь вводит строку из `0` и `1`.
 * Если строка пустая — создается лента со значением по умолчанию `00000`.
 */

void Machine::InputTapeFromConsole() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nВведите начальное состояние ленты (например, 00000): ";

    string tapeStr;
    getline(cin, tapeStr);

    // Если пользователь случайно оставил строку пустой
    if (tapeStr.empty()) {
        cout << "Пустая лента! Установлено значение по умолчанию: 00000\n";
        tapeStr = "00000";
    }
    istringstream ss(tapeStr);
    LoadTape(ss);

    cout << "Лента успешно загружена: " << tapeStr << "\n";
}

/**
 * @brief Ввод последовательности правил из консоли.
 * @details
 * Пользователь вводит строки с номерами, действиями и переходами.
 * Пустая строка завершает ввод.
 */

void Machine::InputProgramFromConsole() {
    rules.clear();
    string line;
    while (true) {
        cout << "Правило #" << rules.size() + 1 << ": ";
        getline(cin, line);

        if (line.empty())
            break;

        istringstream ss(line);
        int ruleNumber, actionInt;
        ss >> ruleNumber >> actionInt;

        Rule::Ruls action = static_cast<Rule::Ruls>(actionInt);

        if (action == Rule::moveIf) {
            int condition, nextIfZero, nextIfOne;
            if (!(ss >> condition >> nextIfZero >> nextIfOne)) {
                cout << "Ошибка: для moveIf нужно 5 чисел: ruleNumber action condition nextIfZero nextIfOne\n";
                continue;
            }
            rules[ruleNumber] = Rule(ruleNumber, action, condition, nextIfZero, nextIfOne);
        } else {
            int nextRule;
            if (!(ss >> nextRule)) {
                cout << "Ошибка: для обычных правил нужно 3 числа: ruleNumber action nextRule\n";
                continue;
            }
            rules[ruleNumber] = Rule(ruleNumber, action, nextRule);
        }
    }
    cout << "\nПрограмма успешно загружена (" << rules.size() << " правил).\n";
}

/**
 * @brief Геттер номера текущего правила.
 * @return Номер текущего правила (`currentRule`).
 */

int Machine::GetCurrentRule() const {
    return currentRule;
}

/**
 * @brief Добавление правила.
 * @param rule - объект правила для добавления.
 */

void Machine::AddRule(const Rule& rule) {
    rules[rule.GetRuleNumber()] = rule;
}

/**
 * @brief Удаление правила по номеру.
 * @details
 * Перед удалением метод проверяет, не ссылаются ли другие правила на указанное.
 * В случае ссылки выводится предупреждение.
 * @param ruleNumber - параметр номера правила, которое будет удалено.
 */

void Machine::RemoveRule(int ruleNumber) {
    auto it = rules.find(ruleNumber);
    if (it != rules.end()) {
        for (auto& [num, rule] : rules) {
            if (rule.GetNextRule() == ruleNumber) {
                cout << "Внимание: правило #" << num
                     << " ссылается на удаляемое правило #" << ruleNumber << "\n";
            }
        }
        rules.erase(it);
        cout << "Правило #" << ruleNumber << " удалено.\n";
    } else {
        cout << "Правило #" << ruleNumber << " не найдено!\n";
    }
}

/**
 * @brief Просмотр текущего списка правил.
 */

void Machine::ShowRules() {
    for (auto& [num, rule] : rules) {
        rule.Show();
    }
}

/**
 * @brief Совершение машиной шага программы.
 * @details
 * Выполняет действие текущего правила и переходит к следующему.
 * Если правило отсутствует — программа завершается.
 */

void Machine::Step() {
    if (currentRule == -1) return;
    auto it = rules.find(currentRule);
    if (it == rules.end()) {
        cout << "Program ended (no such rule " << currentRule << ")\n";
        currentRule = -1;
        return;
    }

    const Rule& rule = it->second;

    switch (rule.GetAction()) {
        case Rule::writeOne:
            tape.WriteOne();
            currentRule = rule.GetNextRule();
            break;

        case Rule::writeZero:
            tape.WriteZero();
            currentRule = rule.GetNextRule();
            break;

        case Rule::moveLeft:
            tape.MoveLeft();
            currentRule = rule.GetNextRule();
            break;

        case Rule::moveRight:
            tape.MoveRight();
            currentRule = rule.GetNextRule();
            break;

        case Rule::moveIf: {
            int symbol = tape.Read();
            if (symbol == rule.GetCondition())
                currentRule = rule.GetNextIfZero();
            else
                currentRule = rule.GetNextIfOne();

            std::cout << "Condition check: symbol=" << symbol
                      << " condition=" << rule.GetCondition()
                      << " → GOTO Rule " << currentRule << "\n";
            break;
        }

        case Rule::end:
            cout << "Program terminated by END\n";
            currentRule = -1;
            break;
    }
}

/**
 * @brief Запуск программы.
 * @details
 * Выполняет последовательные шаги машины до достижения конца (`END` или отсутствия правила).
 * @param log - параметр, который регулирует вывод с деталями о каждом шаге/их отсутствии.
 */
void Machine::Run(bool log) {
    if (currentRule == -1)
        currentRule = 1;
    while (currentRule != -1) {
        Step();
        if (currentRule == -1) break;
        if (log) {
            ShowState();
        }
    }
}

/**
 * @brief Отображение текущего состояния машины.
 * @details
 * Выводит номер активного правила и текущее состояние ленты.
 */

void Machine::ShowState() {
    cout << "---------------------------------\n";
    cout << " Current rule: " << currentRule << endl;
    tape.ShowTape();
}

/**
 * @brief Редактор значений на ленте.
 * @param pos - параметр позиции, на которой произойдёт изменение.
 * @param val - параметр значение, на которое будет изменено исходное.
 */

void Machine::GetTapeToModify(int pos, char val) {
    tape.ModifyTape(pos, val);
}


