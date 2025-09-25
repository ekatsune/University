#include <iostream>
#include <map>
#include "Tape.hpp"
#include "Rule.hpp"

class Machine {
private:
    Tape tape;
    std::map<int,Rule> rules;
    int currentRule;
public:
    Machine();
    void loadProgram(std::istream&);
    void loadTape(std::istream&);
    void addRule(Rule rule);
    void removeRule(int ruleNumber);
    void showRules();
    void step();
    void run();
    void showState();
};