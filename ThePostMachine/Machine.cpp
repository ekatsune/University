#include <istream>
#include "Machine.hpp"
#include "Tape.hpp"
#include "Rule.hpp"
#include <map>
#include <sstream>
#include <limits>
#include <iostream>
using namespace std;

Machine::Machine() : currentRule(1) {}

void Machine::parseConditionalRule(int ruleNumber, Rule::Ruls action,
                                   std::istringstream& ss, const std::string& line) {
    int condition, nextIfZero, nextIfOne;

    if (!(ss >> condition >> nextIfZero >> nextIfOne)) {
        std::cerr << " Ошибка: некорректный формат условного правила:\n"
                  << "   " << line << "\n";
        return;
    }

    rules[ruleNumber] = Rule(ruleNumber, action, condition, nextIfZero, nextIfOne);
}

void Machine::parseRuleLine(const std::string& line) {
    std::istringstream ss(line);

    int ruleNumber, actionInt;
    if (!(ss >> ruleNumber >> actionInt)) {
        std::cerr << "Ошибка: пропущен номер или действие в строке: " << line << "\n";
        return;
    }

    Rule::Ruls action = static_cast<Rule::Ruls>(actionInt);

    if (action == Rule::moveIf)
        parseConditionalRule(ruleNumber, action, ss, line);
    else
        parseSimpleRule(ruleNumber, action, ss, line);
}

void Machine::parseSimpleRule(int ruleNumber, Rule::Ruls action,
                              std::istringstream& ss, const std::string& line) {
    int nextRule;

    if (!(ss >> nextRule)) {
        ss.clear();
        ss.seekg(0);
        int tmpAction;
        ss >> ruleNumber >> tmpAction >> nextRule;
    }

    rules[ruleNumber] = Rule(ruleNumber, action, nextRule);
}

void Machine::LoadProgram(std::istream& in) {
    rules.clear();
    std::string line;

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line.find_first_not_of("01") == std::string::npos) {
            std::istringstream tapeStream(line);
            tapeStream >> tape;
            break;
        }
        parseRuleLine(line);
    }

    in.clear();
    std::cout << "Программа успешно загружена (" << rules.size() << " правил).\n";
}

void Machine::LoadTape(std::istream& in) {
    in >> tape;
}

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

int Machine::GetCurrentRule() const {
    return currentRule;
}

void Machine::AddRule(const Rule& rule) {
    rules[rule.GetRuleNumber()] = rule;
}

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

void Machine::ShowRules() {
    for (auto& [num, rule] : rules) {
        rule.Show();
    }
}

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

void Machine::Run() {
    if (currentRule == -1)
        currentRule = 1;
    while (currentRule != -1) {
        Step();
        if (currentRule == -1) break;
        ShowState();
    }
}

void Machine::ShowState() {
    cout << "---------------------------------\n";
    cout << " Current rule: " << currentRule << endl;
    tape.ShowTape();
}

void Machine::GetTapeToModify(int pos, char val) {
    tape.ModifyTape(pos, val);
}


