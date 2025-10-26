#include "Machine.hpp"
#include "Tape.hpp"
#include "Rule.hpp"
#include <map>
#include <iostream>
using namespace std;

// конструктор: начинаем с первой инструкции
Machine::Machine() : currentRule(0) {}

// ================= ЗАГРУЗКА =================

// загрузка программы из потока (например, из файла или cin)
void Machine::loadProgram(std::istream& in) {
    rules.clear();

    int ruleNumber, action, condition, nextRule;
    while (in >> ruleNumber >> action >> condition >> nextRule) {
        // action - это enum Rule::Ruls (по числу)
        rules[ruleNumber] = Rule(ruleNumber,
                                 static_cast<Rule::Ruls>(action),
                                 condition,
                                 nextRule);
    }
}

// загрузка ленты из потока (например, строка 01001)
void Machine::loadTape(std::istream& in) {
    string line;
    in >> line;

    // лента начинается с позиции 0
    for (char symbol : line) {
        if (symbol == '1') tape.WriteOne();
        else tape.WriteZero();
        tape.MoveRight();
    }

    // вернуть каретку в начало
    for (size_t i = 0; i < line.size(); ++i) {
        tape.MoveLeft();
    }
}

// ================= УПРАВЛЕНИЕ ПРАВИЛАМИ =================

// добавить правило вручную
void Machine::addRule(Rule rule) {
    rules[rule.GetRuleNumber()] = rule;
}

// удалить правило по ruleNumber
void Machine::removeRule(int ruleNumber) {
    rules.erase(ruleNumber);
}

// вывести все правила
void Machine::showRules() {
    for (auto& [num, rule] : rules) {
        cout << "Rule " << num << ": ";
        rule.Show();
    }
}

// ================= ВЫПОЛНЕНИЕ =================

// сделать один шаг (одно правило)
void Machine::step() {
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

        case Rule::moveIf:
            if (tape.Read() == rule.GetCondition()) {
                currentRule = rule.GetNextRule();
            } else {
                auto next = rules.upper_bound(currentRule);
                currentRule = (next == rules.end()) ? -1 : next->first;
            }
            break;

        case Rule::end:
            cout << "Program terminated by END\n";
            currentRule = -1; // признак завершения
            break;
    }
}

// выполнять всю программу до конца
void Machine::run() {
    while (currentRule != -1) {
        step();
        showState(); // для отладки можно оставить
    }
}

// показать текущее состояние (ленту + правило)
void Machine::showState() {
    cout << "Current rule: " << currentRule << endl;
    tape.ShowTape();
}