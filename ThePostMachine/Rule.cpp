/**
 * @file Rule.cpp
 * @brief Реализация класса `Rule`.
 * @details
 * Этот файл содержит реализацию конструкторов и методов класса `Rule`.
 * Реализованы методы: `int GetRuleNumber()const`,`Ruls GetAction() const`,
 * `int GetCondition()const`,`int GetNextRule()const`,`int GetNextIfZero() const`,
 * `int GetNextIfOne() const`,`void Show() const`, перегрузка оператора `operator>>`,
 * а так же конструктор по умолчанию `Rule()` и два конструктора с параметрами:
 * `Rule(int ruleNumber, Ruls action, int nextRule)`,
 * `Rule(int ruleNumber, Ruls action, int condition, int nextIfZero, int nextIfOne)`.
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
 * Создает правило, инициализируя номер правила, действие, условие и два условных переходов а следующие правила.
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
 * @return `condition` - условие наличия символа `0` или `1` под кореткой, которое должно быть проверено.
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
/**@brief Просмотр возможных действий.
 * @details
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


std::istream& operator>>(std::istream& in, Rule& r) {
    int num, act;
    in >> num >> act;

    Rule::Ruls action = static_cast<Rule::Ruls>(act);

    if (action == Rule::moveIf) {
        int cond, j1, j2;
        in >> cond >> j1 >> j2;
        r = Rule(num, action, cond, j1, j2);
    } else {
        int next;
        in >> next;
        r = Rule(num, action, next);
    }

    return in;
}