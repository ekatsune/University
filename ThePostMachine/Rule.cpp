#include "Rule.hpp"
#include <iostream>
Rule::Rule(int ruleNumber, Ruls action, int condition, int nextRule)
        : ruleNumber(ruleNumber), action(action), condition(condition), nextRule(nextRule) {}

int Rule::GetRuleNumber() const {
    return ruleNumber;
}

int Rule::GetCondition() const {
    return condition;
}

int Rule::GetNextRule() const {
    return nextRule;
}

Rule::Ruls Rule::GetAction() const {
    return action;
}
void Rule::Show() const {
    std::cout << "Rule " << ruleNumber << ": ";
    switch (action) {
        case writeOne:  std::cout << "WRITE 1"; break;
        case writeZero: std::cout << "WRITE 0"; break;
        case moveLeft:  std::cout << "MOVE LEFT"; break;
        case moveRight: std::cout << "MOVE RIGHT"; break;
        case moveIf:    std::cout << "IF symbol==" << condition << " THEN GOTO " << nextRule; break;
        case end:       std::cout << "END"; break;
    }
    if (action != moveIf && action != end) {
        std::cout << " ; NEXT -> Rule " << nextRule;
    }
    std::cout << std::endl;
}