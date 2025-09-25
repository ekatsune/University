class Rule {
public:
    enum Ruls {writeOne, writeZero, moveLeft, moveRight, moveIf, end};
    Rule() = default;
    Rule(int ruleNumber,Ruls action, int condition, int nextRule);
    int GetRuleNumber()const;
    int GetCondition()const;
    int GetNextRule()const;
    Ruls GetAction() const;
    void Show() const;
private:

    int ruleNumber;
    int condition;
    int nextRule;
    Ruls action;

};