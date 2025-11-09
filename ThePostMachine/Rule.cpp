/**
 * @file Rule.cpp
 * @brief Реализация класса `Rule`.
 * @details
 * Этот файл содержит реализацию конструкторов и методов класса `Rule`.
 * Реализованы методы:
 * - `int GetRuleNumber()const`
 * - `Ruls GetAction() const`
 * - `int GetCondition()const`
 * - `int GetNextRule()const`
 * - `int GetNextIfZero() const`
 * - `int GetNextIfOne() const`
 * - `void Show() const`
 * Также реализованы:
 * - перегрузка оператора `operator>>`
 * - конструктор по умолчанию `Rule()`
 * - два конструктора с параметрами:
 *  - `Rule(int ruleNumber, Ruls action, int nextRule)`
 *  - `Rule(int ruleNumber, Ruls action, int condition, int nextIfZero, int nextIfOne)`
 * @author Ekatsune
 * @see Rule
 */

#include "Rule.hpp"
#include <iostream>
#include <istream>
/**
 * @brief Конструктор класса по умолчанию.
 * @details
 * Создает правило, инициализируя номер правила = 0, действие - завершение программы машины.
 */
Rule::Rule() :
        ruleNumber(0),
        action(end),
        nextRule(-1),
        condition(-1),
        nextIfZero(-1),
        nextIfOne(-1)
{}
/**
 * @brief Конструктор класса с параметрами.
 * @details
 * Создает правило, инициализируя номер правила, действие и номер следующего правила.
 * Используется для правил, не имеющих условий (например, `WRITE`, `MOVE LEFT`, `MOVE RIGHT`).
 * @param ruleNumber - номер текущего правила.
 * @param action - действие, выполняемое этим правилом.
 * @param nextRule - номер следующего правила, к которому следует перейти.
 */
Rule::Rule(int ruleNumber, Ruls action, int nextRule)
        : ruleNumber(ruleNumber),
          action(action),
          nextRule(nextRule),
          condition(-1),
          nextIfZero(-1),
          nextIfOne(-1)
{}
/**
 * @brief Конструктор класса с параметрами.
 * @details
 * Создает правило, инициализируя номер правила, действие, условие и два возможных переходов.
 * @param ruleNumber - номер текущего правила.
 * @param action - действие, выполняемое этим правилом (`moveIf`).
 * @param condition - проверяемое условие (ожидаемое значение символа под кареткой: `0` или `1`).
 * @param nextIfZero - номер следующего правила, если условие возвращает `0`.
 * @param nextIfOne - номер следующего правила, если условие возвращает `1`.
 */
Rule::Rule(int ruleNumber, Ruls action, int condition, int nextIfZero, int nextIfOne)
        : ruleNumber(ruleNumber),
          action(action),
          nextRule(-1),
          condition(condition),
          nextIfZero(nextIfZero),
          nextIfOne(nextIfOne)
{}
/**@brief Геттер номера правила.
 * @return `ruleNumber` - номер текущего правила.
 * */
int Rule::GetRuleNumber() const {
    return ruleNumber;
}
/**@brief Геттер условия.
 * @return `condition` - условие проверки `0` или `1` под кореткой, которое должно быть проверено.
 * */
int Rule::GetCondition() const {
    return condition;
}
/**@brief Геттер номера следующего правила.
 * @return `nextRule` - номер следующего правила.
 * */
int Rule::GetNextRule() const {
    return nextRule;
}
/**@brief Геттер номера условного следующего правила.
 * @return `nextIfZero` - номер следующего правила, если было условие и проверка `0`.
 * */
int Rule::GetNextIfZero() const { return nextIfZero; }
/**@brief Геттер номера условного следующего правила.
 * @return `nextIfOne` - номер следующего правила, если было условие и проверка `1`.
 * */
int Rule::GetNextIfOne() const { return nextIfOne; }
/**@brief Геттер действия.
 * @return `action` - действие, которое должно быть выполнено в ходе исполнения
 * правила.
 * */
Rule::Ruls Rule::GetAction() const {
    return action;
}
/**@brief Просмотр деталей текущего правила.
 * */
void Rule::Show() const {
    std::cout << "Правило " << ruleNumber << ": ";

    switch (action) {
        case writeOne: std::cout << "WRITE 1 ; NEXT -> Rule " << nextRule;
            break;
        case writeZero: std::cout << "WRITE 0 ; NEXT -> Rule " << nextRule;
            break;
        case moveLeft: std::cout << "MOVE LEFT ; NEXT -> Rule " << nextRule;
            break;
        case moveRight: std::cout << "MOVE RIGHT ; NEXT -> Rule " << nextRule;
            break;
        case moveIf: std::cout << "? (IF symbol==" << condition
                      << " THEN Rule " << nextIfZero
                      << " ELSE Rule " << nextIfOne << ")";
            break;
        case end:std::cout << "END";
            break;
    }
    std::cout << std::endl;
}

/**
 * @brief Перегрузка оператора ввода `>>`.
 * @details
 * Позволяет считать правило из входного потока (например, из файла или консоли).
 * Формат ввода:
 * ```
 * ruleNumber action [condition nextIfZero nextIfOne] | [nextRule]
 * ```
 * где:
 * - если `action == moveIf`, читаются 5 чисел;
 * - иначе читаются 3 числа.
 *
 * @param input Входной поток (`std::istream`).
 * @param rule Объект `Rule`, в который будут записаны считанные данные.
 * @return Ссылка на входной поток `input`.
 *
 * @see Rule::Ruls
 */

std::istream& operator>>(std::istream& input, Rule& rule) {
    int num, act;
    input >> num >> act;

    Rule::Ruls action = static_cast<Rule::Ruls>(act);

    if (action == Rule::moveIf) {
        int cond, j1, j2;
        input >> cond >> j1 >> j2;
        rule = Rule(num, action, cond, j1, j2);
    } else {
        int next;
        input >> next;
        rule = Rule(num, action, next);
    }

    return input;
}