#include <gtest/gtest.h>
#include <sstream>
#include "../Tape.hpp"
#include "../Rule.hpp"
#include "../Machine.hpp"

/**
 * @file test1.cpp
 * @brief Unit тесты.
 * @details
 * Этот файл содержит 58 Unit.
 * Покрытие тестами составляет 95% строк файла Machine.cpp,
 * 90% - Rule.cpp, 94% - Tape.cpp.
 *
 * @author Ekatsune
 * @see Machine, Rule, Tape
 */

TEST(TapeTest, DefaultConstructorSetsZeroAtStart) {
    Tape t;
    EXPECT_EQ(t.Read(), 0) << "После создания ленты начальный символ должен быть 0";
}

TEST(TapeTest, WriteOneSetsSymbolToOne) {
    Tape t;
    t.WriteOne();
    EXPECT_EQ(t.Read(), 1);
}

TEST(TapeTest, WriteZeroOverwritesOne) {
    Tape t;
    t.WriteOne();
    t.WriteZero();
    EXPECT_EQ(t.Read(), 0);
}

TEST(TapeTest, MoveRightChangesPosition) {
    Tape t;
    t.WriteOne();
    t.MoveRight();
    EXPECT_EQ(t.Read(), 0) << "После MoveRight новая ячейка должна быть 0";
}

TEST(TapeTest, MoveLeftChangesPosition) {
    Tape t;
    t.MoveRight();
    t.WriteOne();
    t.MoveLeft();
    EXPECT_EQ(t.Read(), 0);
}

TEST(TapeTest, MultipleWriteAndReadPositions) {
    Tape t;
    t.WriteOne();
    t.MoveRight();
    t.WriteZero();
    t.MoveRight();
    t.WriteOne();

    t.MoveLeft();
    t.MoveLeft();
    EXPECT_EQ(t.Read(), 1);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

TEST(TapeTest, InputOperatorLoadsTapeCorrectly) {
    std::istringstream input("10101\n");
    Tape t;
    input >> t;

    t.MoveRight();
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

TEST(TapeTest, InputOperatorSkipsEmptyLines) {
    std::istringstream input("\n\n0101\n");
    Tape t;
    input >> t;
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

TEST(TapeTest, ModifyTapeChangesValue) {
    Tape t;
    t.WriteZero();
    t.ModifyTape(0, '1');
    EXPECT_EQ(t.Read(), 1);
}

TEST(TapeTest, ModifyTapeThrowsOnInvalidValue) {
    Tape t;
    EXPECT_THROW(t.ModifyTape(0, 'x'), std::invalid_argument);
}

TEST(RuleTest, SimpleConstructorSetsFieldsCorrectly) {
    Rule r(1, Rule::writeOne, 2);
    EXPECT_EQ(r.GetRuleNumber(), 1);
    EXPECT_EQ(r.GetAction(), Rule::writeOne);
    EXPECT_EQ(r.GetNextRule(), 2);
    EXPECT_EQ(r.GetCondition(), -1);
    EXPECT_EQ(r.GetNextIfZero(), -1);
    EXPECT_EQ(r.GetNextIfOne(), -1);
}

TEST(RuleTest, ConditionalConstructorSetsFieldsCorrectly) {
    Rule r(5, Rule::moveIf, 1, 2, 3);
    EXPECT_EQ(r.GetRuleNumber(), 5);
    EXPECT_EQ(r.GetAction(), Rule::moveIf);
    EXPECT_EQ(r.GetCondition(), 1);
    EXPECT_EQ(r.GetNextIfZero(), 2);
    EXPECT_EQ(r.GetNextIfOne(), 3);
    EXPECT_EQ(r.GetNextRule(), -1);
}

TEST(RuleTest, GettersReturnExpectedValues) {
    Rule r(10, Rule::moveRight, 11);
    EXPECT_EQ(r.GetRuleNumber(), 10);
    EXPECT_EQ(r.GetAction(), Rule::moveRight);
    EXPECT_EQ(r.GetNextRule(), 11);
}

TEST(RuleTest, InputOperatorReadsSimpleRule) {
    std::istringstream in("7 1 8");
    Rule r(0, Rule::writeZero, 0);
    in >> r;

    EXPECT_EQ(r.GetRuleNumber(), 7);
    EXPECT_EQ(r.GetAction(), Rule::writeOne);
    EXPECT_EQ(r.GetNextRule(), 8);
}

TEST(RuleTest, InputOperatorReadsConditionalRule) {
    std::istringstream in("3 5 1 4 6");
    Rule r(0, Rule::writeZero, 0);
    in >> r;

    EXPECT_EQ(r.GetRuleNumber(), 3);
    EXPECT_EQ(r.GetAction(), Rule::moveIf);
    EXPECT_EQ(r.GetCondition(), 1);
    EXPECT_EQ(r.GetNextIfZero(), 4);
    EXPECT_EQ(r.GetNextIfOne(), 6);
}

TEST(RuleTest, WriteZeroActionStoredCorrectly) {
    Rule r(2, Rule::writeZero, 3);
    EXPECT_EQ(r.GetAction(), Rule::writeZero);
    EXPECT_EQ(r.GetNextRule(), 3);
}

TEST(RuleTest, MoveLeftActionStoredCorrectly) {
    Rule r(4, Rule::moveLeft, 5);
    EXPECT_EQ(r.GetAction(), Rule::moveLeft);
    EXPECT_EQ(r.GetNextRule(), 5);
}

TEST(RuleTest, EndActionHasNoNextRule) {
    Rule r(9, Rule::end, -1);
    EXPECT_EQ(r.GetAction(), Rule::end);
    EXPECT_EQ(r.GetNextRule(), -1);
}

TEST(RuleTest, ShowOutputsCorrectTextForSimpleRule) {
    Rule r(1, Rule::writeOne, 2);
    std::ostringstream out;
    std::streambuf* oldCout = std::cout.rdbuf(out.rdbuf());
    r.Show();
    std::cout.rdbuf(oldCout);

    std::string output = out.str();
    EXPECT_NE(output.find("WRITE 1"), std::string::npos);
    EXPECT_NE(output.find("Rule 2"), std::string::npos);
}

TEST(RuleTest, ShowOutputsCorrectTextForConditionalRule) {
    Rule r(2, Rule::moveIf, 1, 4, 5);
    std::ostringstream out;
    std::streambuf* oldCout = std::cout.rdbuf(out.rdbuf());
    r.Show();
    std::cout.rdbuf(oldCout);

    std::string output = out.str();
    EXPECT_NE(output.find("IF symbol==1"), std::string::npos);
    EXPECT_NE(output.find("THEN Rule 4"), std::string::npos);
    EXPECT_NE(output.find("ELSE Rule 5"), std::string::npos);
}

TEST(MachineTest, DefaultConstructorSetsCurrentRuleToOne) {
    Machine m;
    EXPECT_EQ(m.GetCurrentRule(), 1);
}

TEST(MachineTest, AddRuleInsertsRule) {
    Machine m;
    Rule r(1, Rule::writeOne, 2);
    m.AddRule(r);
    m.ShowRules();
    EXPECT_NO_THROW(m.ShowRules());
}

TEST(MachineTest, RemoveExistingRule) {
    Machine m;
    Rule r(1, Rule::writeZero, 2);
    m.AddRule(r);

    testing::internal::CaptureStdout();
    m.RemoveRule(1);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("удалено"), std::string::npos);
}

TEST(MachineTest, RemoveNonExistingRule) {
    Machine m;
    testing::internal::CaptureStdout();
    m.RemoveRule(42);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("не найдено"), std::string::npos);
}

TEST(MachineTest, RunSimpleProgramWritesOne) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::end, -1));

    testing::internal::CaptureStdout();
    m.Run(false);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Program terminated by END"), std::string::npos);
}

TEST(MachineTest, StepWriteZero) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeZero, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, StepMoveRightChangesTapePosition) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, StepConditionalRuleConditionMatches) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));

    testing::internal::CaptureStdout();
    m.Step();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("GOTO Rule 2"), std::string::npos);
}

TEST(MachineTest, StepConditionalRuleConditionNotMatch) {
    Machine m;
    m.GetTapeToModify(0, '1');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));

    testing::internal::CaptureStdout();
    m.Step();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("GOTO Rule 3"), std::string::npos);
}

TEST(MachineTest, StepWithMissingRuleTerminatesProgram) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, 99));
    testing::internal::CaptureStdout();
    m.Run(false);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

TEST(MachineTest, ParseSimpleRuleLineCreatesRule) {
    Machine m;
    m.ParseRuleLine("1 1 2"); // writeOne  → next=2
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("WRITE 1"), std::string::npos);
}


TEST(MachineTest, ParseConditionalRuleLineCreatesRule) {
    Machine m;
    m.ParseRuleLine("2 5 0 3 4"); // moveIf
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("IF symbol==0"), std::string::npos);
}

TEST(MachineTest, LoadProgramReadsRulesAndTape) {
    std::string data =
            "1 2 2\n"
            "2 6 -1\n"
            "0101\n";
    std::istringstream in(data);
    Machine m;

    testing::internal::CaptureStdout();
    m.LoadProgram(in);
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Программа успешно загружена"), std::string::npos);
}

TEST(MachineTest, GetTapeToModifyChangesTape) {
    Machine m;
    EXPECT_NO_THROW(m.GetTapeToModify(0, '1'));
}

TEST(MachineTest, ShowStateDoesNotThrow) {
    Machine m;
    EXPECT_NO_THROW(m.ShowState());
}

TEST(MachineTest, StepMoveLeftChangesTapePosition) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveLeft, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, StepEndTerminatesProgram) {
    Machine m;
    m.AddRule(Rule(1, Rule::end, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, RunMultipleSteps) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));
    m.AddRule(Rule(3, Rule::end, -1));

    m.Run(false );
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, LoadTapeEmptyString) {
    Machine m;
    std::istringstream ss("");
    EXPECT_NO_THROW(m.LoadTape(ss));
}

TEST(MachineTest, RemoveRuleWithReferences) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));

    testing::internal::CaptureStdout();
    m.RemoveRule(2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("ссылается на удаляемое правило"), std::string::npos);
}

TEST(MachineTest, StepConditionalRuleWithNonMatchingSymbol) {
    Machine m;
    m.GetTapeToModify(0, '1');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));

    testing::internal::CaptureStdout();
    m.Step();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("GOTO Rule 3"), std::string::npos);
}

TEST(MachineTest, LoadProgramSkipsEmptyLinesBeforeTape) {
    std::string data =
            "\n\n\n1 1 2\n0101\n";
    std::istringstream in(data);
    Machine m;

    testing::internal::CaptureStdout();
    m.LoadProgram(in);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Программа успешно загружена"), std::string::npos);
}

TEST(MachineTest, StepMultipleMoveRight) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, 2));
    m.AddRule(Rule(2, Rule::moveRight, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 2);
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, StepMultipleMoveLeft) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveLeft, 2));
    m.AddRule(Rule(2, Rule::moveLeft, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 2);
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

TEST(MachineTest, LoadTapeAllZerosViaShowTape) {
    Machine m;
    std::istringstream ss("00000");
    m.LoadTape(ss);

    testing::internal::CaptureStdout();
    m.ShowState();  // вызывает ShowTape внутри
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("[0]"), std::string::npos);
}

TEST(MachineTest, LoadTapeAllOnesViaShowTape) {
    Machine m;
    std::istringstream ss("11111");
    m.LoadTape(ss);

    testing::internal::CaptureStdout();
    m.ShowState();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("[1]"), std::string::npos);
}

TEST(MachineTest, StepConditionalMultipleMatches) {
    Machine m;
    m.GetTapeToModify(0, '0');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));
    m.AddRule(Rule(2, Rule::writeOne, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 2);
}

TEST(MachineTest, StepConditionalMultipleNotMatch) {
    Machine m;
    m.GetTapeToModify(0, '1');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));
    m.AddRule(Rule(3, Rule::writeZero, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 3);
}

TEST(MachineTest, LoadProgramWithInvalidRuleLine) {
    std::string data =
            "abc def\n0101\n";
    std::istringstream in(data);
    Machine m;

    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    m.LoadProgram(in);

    std::cerr.rdbuf(old);
    std::string out = buffer.str();

    EXPECT_NE(out.find("Ошибка"), std::string::npos);
}

TEST(MachineTest, InputTapeFromConsoleEmpty) {
    Machine m;
    std::istringstream input("\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    m.InputTapeFromConsole();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Пустая лента"), std::string::npos);

    std::cin.rdbuf(orig);
}

TEST(MachineTest, AddMultipleRulesAndShow) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));
    EXPECT_NO_THROW(m.ShowRules());
}

TEST(MachineTest, StepWithNonExistentCurrentRule) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    testing::internal::CaptureStdout();
    m.Step(); // currentRule=1 exists
    m.Step(); // currentRule=2 missing
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

TEST(MachineTest, ParseConditionalRuleInvalidInput) {
    Machine m;
    std::istringstream ss("a b c");
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    m.ParseConditionalRule(1, Rule::moveIf, ss, "a b c");

    std::cerr.rdbuf(old);
    std::string out = buffer.str();
    EXPECT_NE(out.find("Ошибка"), std::string::npos);
}

TEST(MachineTest, ParseSimpleRuleFallbackOldFormat) {
    Machine m;
    std::istringstream ss("1 1");
    m.ParseSimpleRule(1, Rule::writeOne, ss);
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("WRITE 1"), std::string::npos);
}

TEST(MachineTest, StepWithCurrentRuleMinusOne) {
    Machine m;
    m.Step();
    m.AddRule(Rule(1, Rule::end, -1));
    m.Step();
    EXPECT_NO_THROW(m.Step());
}

TEST(MachineTest, RunWithNoRules) {
    Machine m;
    m.RemoveRule(1);
    testing::internal::CaptureStdout();
    m.Run(false);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

TEST(MachineTest, InputProgramFromConsoleInvalidMoveIf) {
    Machine m;
    std::istringstream input("1 5 0\n\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    m.InputProgramFromConsole();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Ошибка: для moveIf нужно 5 чисел"), std::string::npos);

    std::cin.rdbuf(orig);
}

TEST(MachineTest, InputProgramFromConsoleInvalidSimpleRule) {
    Machine m;
    std::istringstream input("2 1\n\n"); // мало чисел
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    m.InputProgramFromConsole();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Ошибка: для обычных правил нужно 3 числа"), std::string::npos);

    std::cin.rdbuf(orig);
}

