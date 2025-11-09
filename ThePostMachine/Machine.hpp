#pragma once
#include <iostream>
#include <map>
#include "Tape.hpp"
#include "Rule.hpp"
#include <istream>
/**
 * @class Machine
 * @brief Класс реализующий работу машины Поста.
 */
class Machine {
private:
    /**
     * @brief объект класса Tape.
     */
    Tape tape;
    /**
     * @brief Список правил <номер, объект класса Rule>.
     */
    std::map<int,Rule> rules;
    /**
     * @brief Поле номера текущего правила.
     */
    int currentRule;
public:
    /**
     * @brief Геттер номера текущего правила.
     */
    int GetCurrentRule() const;
    /**
     * @brief Загрузка программы из входного потока.
     */
    void LoadProgram(std::istream& input);
    /**
     * @brief Инициализация ленты.
     */
    void LoadTape(std::istream& input);
    /**
     * @brief Разбор строки с правилом.
     */
    void ParseRuleLine(const std::string& line);
    /**
     * @brief Разбиение строки на парметры не условного правила.
     */
    void ParseSimpleRule(int ruleNumber, Rule::Ruls action,
                         std::istringstream& ss);
    /**
    * @brief Разбиение строки на парметры условного правила.
    */
    void ParseConditionalRule(int ruleNumber, Rule::Ruls action,
                              std::istringstream& ss, const std::string& line);
    /**
     * @brief Ввод ленты из консоли.
     */
    void InputTapeFromConsole();
    /**
     *
     * @brief Ввод последовательности правил из консоли.
     */
    void InputProgramFromConsole();
    /**
     * @brief Конструктор машины Поста.
     */
    Machine();
    /**
     * @brief Добавление правила.
     */
    void AddRule(const Rule& rule);
    /**
     * @brief Удаление правила по номеру.
     */
    void RemoveRule(int ruleNumber);
    /**
     * @brief Просмотр текущего списка правил.
     */
    void ShowRules();
    /**
     * @brief Совершение машиной шага программы.
     */
    void Step();
    /**
     * @brief Запуск программы.
     */
    void Run(bool log);
    /**
     * @brief Вывод информации о текущем правиле.
     */
    void ShowState();
    /**
     * @brief Редактор значений на ленте.
     */
    void GetTapeToModify(int pos, char val);
};