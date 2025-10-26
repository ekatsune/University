#pragma once
#include <iostream>
#include <map>
#include "Tape.hpp"
#include "Rule.hpp"
#include <istream>

class Machine {
private:
    Tape tape;
    std::map<int,Rule> rules;
    int currentRule;
public:
    int GetCurrentRule() const;
    void LoadProgram(std::istream& in);
    void parseRuleLine(const std::string& line);
    void parseSimpleRule(int ruleNumber, Rule::Ruls action,
                         std::istringstream& ss, const std::string& line);
    void parseConditionalRule(int ruleNumber, Rule::Ruls action,
                              std::istringstream& ss, const std::string& line);

    void InputTapeFromConsole();
    void InputProgramFromConsole();
    Machine();
    void LoadTape(std::istream& in);
    void AddRule(const Rule& rule);
    void RemoveRule(int ruleNumber);
    void ShowRules();
    void Step();
    void Run();
    void ShowState();
    void GetTapeToModify(int pos, char val);
};