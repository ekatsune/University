#pragma once
#include <istream>
/**
 * @class Rule
 * @brief Класс реализующий логику работы с правилами.
 */
class Rule {
public:
    /**
     * @brief Перечисление корректных номеров действий правил.
     */
    enum Ruls {writeOne = 1, writeZero, moveLeft, moveRight, moveIf, end};
    /**
     * @brief Конструктор правила без параметров.
     */
    Rule();
    /**
    * @brief Конструктор правила с параметрами для не условных правил.
    */
    Rule(int ruleNumber, Ruls action, int nextRule);
    /**
    * @brief Конструктор правила с параметрами для условных правил.
    */
    Rule(int ruleNumber, Ruls action, int condition, int nextIfZero, int nextIfOne);
    /**
     * @brief Геттер номера текущего правила.
     */
    int GetRuleNumber()const;
    /**
     * @brief Геттер действия текущего правила.
     */
    Ruls GetAction() const;
    /**
     * @brief Геттер условия правила.
     */
    int GetCondition()const;
    /**
     * @brief Геттер номера следующего правила.
     */
    int GetNextRule()const;
    /**
     * @brief Геттер номера следующего правила, если условие = 0.
     */
    int GetNextIfZero() const;
    /**
    * @brief Геттер номера следующего правила, если условие = 1.
    */
    int GetNextIfOne() const;
    /**@brief Просмотр деталей текущего правила.
    * */
    void Show() const;
private:
    /**
     * @brief Поле ноемра текущего правила.
     */
    int ruleNumber;
    /**
     * @brief Поле дейтсвия првила.
     */
    Ruls action;
    /**
     * @brief Поле номера следующего правила.
     */
    int nextRule;
    /**
     * @brief Поле условия правила.
     */
    int condition;
    /**
     * @brief Поле номера следующего правила, если условие = 0.
     */
    int nextIfZero;
    /**
     * @brief Поле номера следующего правила, если условие = 1.
     */
    int nextIfOne;
    /**
     * @brief Перегрузка оператора.
     */
    friend std::istream& operator>>(std::istream& input, Rule& rule);

};

