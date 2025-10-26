#pragma once
#include <istream>
class Rule {
public:
    enum Ruls {writeOne = 1, writeZero, moveLeft, moveRight, moveIf, end};
    Rule();
    Rule(int ruleNumber, Ruls action, int nextRule);
    Rule(int ruleNumber, Ruls action, int condition, int nextIfZero, int nextIfOne);

    int GetRuleNumber()const;
    Ruls GetAction() const;
    int GetCondition()const;
    int GetNextRule()const;
    int GetNextIfZero() const;
    int GetNextIfOne() const;
    void Show() const;
private:

    int ruleNumber;
    Ruls action;
    int nextRule;
    int condition;
    int nextIfZero;
    int nextIfOne;
    friend std::istream& operator>>(std::istream& in, Rule& r);

};

