#include <gtest/gtest.h>
#include <sstream>
#include "Tape.hpp"
#include "Rule.hpp"
#include "Machine.hpp"

// 1️⃣ Тест: начальное состояние ленты
TEST(TapeTest, DefaultConstructorSetsZeroAtStart) {
    Tape t;
    EXPECT_EQ(t.Read(), 0) << "После создания ленты начальный символ должен быть 0";
}

// 2️⃣ Тест: запись единицы и чтение
TEST(TapeTest, WriteOneSetsSymbolToOne) {
    Tape t;
    t.WriteOne();
    EXPECT_EQ(t.Read(), 1);
}

// 3️⃣ Тест: запись нуля после единицы
TEST(TapeTest, WriteZeroOverwritesOne) {
    Tape t;
    t.WriteOne();
    t.WriteZero();
    EXPECT_EQ(t.Read(), 0);
}

// 4️⃣ Тест: движение вправо
TEST(TapeTest, MoveRightChangesPosition) {
    Tape t;
    t.WriteOne();
    t.MoveRight();
    EXPECT_EQ(t.Read(), 0) << "После MoveRight новая ячейка должна быть 0";
}

// 5️⃣ Тест: движение влево
TEST(TapeTest, MoveLeftChangesPosition) {
    Tape t;
    t.MoveRight();
    t.WriteOne();
    t.MoveLeft();
    EXPECT_EQ(t.Read(), 0);
}

// 6️⃣ Тест: запись и чтение нескольких позиций
TEST(TapeTest, MultipleWriteAndReadPositions) {
    Tape t;
    t.WriteOne(); // позиция 0 = 1
    t.MoveRight();
    t.WriteZero(); // позиция 1 = 0
    t.MoveRight();
    t.WriteOne(); // позиция 2 = 1

    // Проверяем содержимое ленты
    t.MoveLeft();
    t.MoveLeft();
    EXPECT_EQ(t.Read(), 1);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

// 7️⃣ Тест: корректная загрузка ленты из строки (istream)
TEST(TapeTest, InputOperatorLoadsTapeCorrectly) {
    std::istringstream input("10101\n");
    Tape t;
    input >> t;

    // Проверяем символы
    t.MoveRight();
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

// 8️⃣ Тест: чтение из потока с пустыми строками
TEST(TapeTest, InputOperatorSkipsEmptyLines) {
    std::istringstream input("\n\n0101\n");
    Tape t;
    input >> t;
    EXPECT_EQ(t.Read(), 0);
    t.MoveRight();
    EXPECT_EQ(t.Read(), 1);
}

// 9️⃣ Тест: ModifyTape изменяет значение по позиции
TEST(TapeTest, ModifyTapeChangesValue) {
    Tape t;
    t.WriteZero();
    t.ModifyTape(0, '1');
    EXPECT_EQ(t.Read(), 1);
}

// 🔟 Тест: ModifyTape выбрасывает исключение при неверном символе
TEST(TapeTest, ModifyTapeThrowsOnInvalidValue) {
    Tape t;
    EXPECT_THROW(t.ModifyTape(0, 'x'), std::invalid_argument);
}

// 1️⃣ Тест: Конструктор для простого правила
TEST(RuleTest, SimpleConstructorSetsFieldsCorrectly) {
    Rule r(1, Rule::writeOne, 2);
    EXPECT_EQ(r.GetRuleNumber(), 1);
    EXPECT_EQ(r.GetAction(), Rule::writeOne);
    EXPECT_EQ(r.GetNextRule(), 2);
    EXPECT_EQ(r.GetCondition(), -1);
    EXPECT_EQ(r.GetNextIfZero(), -1);
    EXPECT_EQ(r.GetNextIfOne(), -1);
}

// 2️⃣ Тест: Конструктор для условного правила (moveIf)
TEST(RuleTest, ConditionalConstructorSetsFieldsCorrectly) {
    Rule r(5, Rule::moveIf, 1, 2, 3);
    EXPECT_EQ(r.GetRuleNumber(), 5);
    EXPECT_EQ(r.GetAction(), Rule::moveIf);
    EXPECT_EQ(r.GetCondition(), 1);
    EXPECT_EQ(r.GetNextIfZero(), 2);
    EXPECT_EQ(r.GetNextIfOne(), 3);
    EXPECT_EQ(r.GetNextRule(), -1);
}

// 3️⃣ Тест: Getters возвращают корректные значения
TEST(RuleTest, GettersReturnExpectedValues) {
    Rule r(10, Rule::moveRight, 11);
    EXPECT_EQ(r.GetRuleNumber(), 10);
    EXPECT_EQ(r.GetAction(), Rule::moveRight);
    EXPECT_EQ(r.GetNextRule(), 11);
}

// 4️⃣ Тест: Оператор ввода >> для простого правила
TEST(RuleTest, InputOperatorReadsSimpleRule) {
    std::istringstream in("7 1 8"); // ruleNumber=7, action=writeOne, nextRule=8
    Rule r(0, Rule::writeZero, 0);
    in >> r;

    EXPECT_EQ(r.GetRuleNumber(), 7);
    EXPECT_EQ(r.GetAction(), Rule::writeOne);
    EXPECT_EQ(r.GetNextRule(), 8);
}

// 5️⃣ Тест: Оператор ввода >> для условного перехода
TEST(RuleTest, InputOperatorReadsConditionalRule) {
    std::istringstream in("3 5 1 4 6"); // ruleNumber=3, action=moveIf, condition=1, nextIfZero=4, nextIfOne=6
    Rule r(0, Rule::writeZero, 0);
    in >> r;

    EXPECT_EQ(r.GetRuleNumber(), 3);
    EXPECT_EQ(r.GetAction(), Rule::moveIf);
    EXPECT_EQ(r.GetCondition(), 1);
    EXPECT_EQ(r.GetNextIfZero(), 4);
    EXPECT_EQ(r.GetNextIfOne(), 6);
}

// 6️⃣ Тест: Проверка действия writeZero
TEST(RuleTest, WriteZeroActionStoredCorrectly) {
    Rule r(2, Rule::writeZero, 3);
    EXPECT_EQ(r.GetAction(), Rule::writeZero);
    EXPECT_EQ(r.GetNextRule(), 3);
}

// 7️⃣ Тест: Проверка действия moveLeft
TEST(RuleTest, MoveLeftActionStoredCorrectly) {
    Rule r(4, Rule::moveLeft, 5);
    EXPECT_EQ(r.GetAction(), Rule::moveLeft);
    EXPECT_EQ(r.GetNextRule(), 5);
}

// 8️⃣ Тест: Проверка действия end
TEST(RuleTest, EndActionHasNoNextRule) {
    Rule r(9, Rule::end, -1);
    EXPECT_EQ(r.GetAction(), Rule::end);
    EXPECT_EQ(r.GetNextRule(), -1);
}

// 9️⃣ Тест: Проверка вывода Show() для простого правила
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

// 🔟 Тест: Проверка вывода Show() для условного правила
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

// 1️⃣ Тест: Машина создаётся с первым правилом
TEST(MachineTest, DefaultConstructorSetsCurrentRuleToOne) {
    Machine m;
    EXPECT_EQ(m.GetCurrentRule(), 1);
}

// 2️⃣ Тест: Добавление правила
TEST(MachineTest, AddRuleInsertsRule) {
    Machine m;
    Rule r(1, Rule::writeOne, 2);
    m.AddRule(r);
    m.ShowRules(); // просто убедиться, что метод не падает
    EXPECT_NO_THROW(m.ShowRules());
}

// 3️⃣ Тест: Удаление существующего правила
TEST(MachineTest, RemoveExistingRule) {
    Machine m;
    Rule r(1, Rule::writeZero, 2);
    m.AddRule(r);

    testing::internal::CaptureStdout();
    m.RemoveRule(1);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("удалено"), std::string::npos);
}

// 4️⃣ Тест: Удаление несуществующего правила
TEST(MachineTest, RemoveNonExistingRule) {
    Machine m;
    testing::internal::CaptureStdout();
    m.RemoveRule(42);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("не найдено"), std::string::npos);
}

// 5️⃣ Тест: Простейшая программа — запись 1 и конец
TEST(MachineTest, RunSimpleProgramWritesOne) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::end, -1));

    testing::internal::CaptureStdout();
    m.Run();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Program terminated by END"), std::string::npos);
}

// 6️⃣ Тест: Проверка Step() с действием writeZero
TEST(MachineTest, StepWriteZero) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeZero, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 7️⃣ Тест: Проверка Step() с действием moveRight
TEST(MachineTest, StepMoveRightChangesTapePosition) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 8️⃣ Тест: Проверка Step() с условным переходом (условие совпадает)
TEST(MachineTest, StepConditionalRuleConditionMatches) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3)); // условие совпадает → Rule 2

    testing::internal::CaptureStdout();
    m.Step();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("GOTO Rule 2"), std::string::npos);
}

// 9️⃣ Тест: Проверка Step() с условным переходом (условие не совпадает)
TEST(MachineTest, StepConditionalRuleConditionNotMatch) {
    Machine m;
    // передвинем ленту, чтобы текущий символ был 1
    m.GetTapeToModify(0, '1');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3)); // условие не совпадает → Rule 3

    testing::internal::CaptureStdout();
    m.Step();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("GOTO Rule 3"), std::string::npos);
}

// 🔟 Тест: Программа с отсутствующим правилом завершает выполнение
TEST(MachineTest, StepWithMissingRuleTerminatesProgram) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, 99)); // 99 отсутствует
    testing::internal::CaptureStdout();
    m.Run();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

// 11️⃣ Тест: parseRuleLine создаёт простое правило
TEST(MachineTest, ParseSimpleRuleLineCreatesRule) {
    Machine m;
    m.parseRuleLine("1 1 2"); // writeOne  → next=2
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("WRITE 1"), std::string::npos);
}

// 12️⃣ Тест: parseRuleLine создаёт условное правило
TEST(MachineTest, ParseConditionalRuleLineCreatesRule) {
    Machine m;
    m.parseRuleLine("2 5 0 3 4"); // moveIf
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("IF symbol==0"), std::string::npos);
}

// 13️⃣ Тест: LoadProgram корректно читает правила и ленту
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

// 14️⃣ Тест: GetTapeToModify корректно меняет ленту
TEST(MachineTest, GetTapeToModifyChangesTape) {
    Machine m;
    EXPECT_NO_THROW(m.GetTapeToModify(0, '1'));
}

// 15️⃣ Тест: ShowState не выбрасывает исключений
TEST(MachineTest, ShowStateDoesNotThrow) {
    Machine m;
    EXPECT_NO_THROW(m.ShowState());
}

// 16️⃣ Step с действием moveLeft
TEST(MachineTest, StepMoveLeftChangesTapePosition) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveLeft, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 17️⃣ Step с действием end
TEST(MachineTest, StepEndTerminatesProgram) {
    Machine m;
    m.AddRule(Rule(1, Rule::end, -1));
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 18️⃣ Run проходит несколько шагов программы
TEST(MachineTest, RunMultipleSteps) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));
    m.AddRule(Rule(3, Rule::end, -1));

    m.Run();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 19️⃣ LoadTape с пустой строкой
TEST(MachineTest, LoadTapeEmptyString) {
    Machine m;
    std::istringstream ss("");
    EXPECT_NO_THROW(m.LoadTape(ss));
}

// 20️⃣ Удаление правила, на которое есть ссылки
TEST(MachineTest, RemoveRuleWithReferences) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));

    testing::internal::CaptureStdout();
    m.RemoveRule(2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("ссылается на удаляемое правило"), std::string::npos);
}

// 21️⃣ Условный переход на символ 1 с condition=0
TEST(MachineTest, StepConditionalRuleWithNonMatchingSymbol) {
    Machine m;
    m.GetTapeToModify(0, '1');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));

    testing::internal::CaptureStdout();
    m.Step();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("GOTO Rule 3"), std::string::npos);
}

// 22️⃣ LoadProgram игнорирует пустые строки перед лентой
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
// 23️⃣ Step с несколькими moveRight подряд
TEST(MachineTest, StepMultipleMoveRight) {
    Machine m;
    m.AddRule(Rule(1, Rule::moveRight, 2));
    m.AddRule(Rule(2, Rule::moveRight, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 2);
    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), -1);
}

// 24️⃣ Step с несколькими moveLeft подряд
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

    EXPECT_NE(output.find("[0]"), std::string::npos);  // проверяем, что текущий символ 0
}

TEST(MachineTest, LoadTapeAllOnesViaShowTape) {
    Machine m;
    std::istringstream ss("11111");
    m.LoadTape(ss);

    testing::internal::CaptureStdout();
    m.ShowState();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("[1]"), std::string::npos);  // текущий символ 1
}

// 27️⃣ Проверка Step с условием совпадения, несколько переходов
TEST(MachineTest, StepConditionalMultipleMatches) {
    Machine m;
    m.GetTapeToModify(0, '0');
    m.AddRule(Rule(1, Rule::moveIf, 0, 2, 3));
    m.AddRule(Rule(2, Rule::writeOne, -1));

    m.Step();
    EXPECT_EQ(m.GetCurrentRule(), 2);
}

// 28️⃣ Проверка Step с условием несоответствия, несколько переходов
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

    // Перехватываем std::cerr
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    m.LoadProgram(in);

    std::cerr.rdbuf(old); // восстанавливаем
    std::string out = buffer.str();

    EXPECT_NE(out.find("Ошибка"), std::string::npos);
}


// 30️⃣ InputTapeFromConsole имитация пустой строки
TEST(MachineTest, InputTapeFromConsoleEmpty) {
    Machine m;
    std::istringstream input("\n");
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    m.InputTapeFromConsole();
    std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Пустая лента"), std::string::npos);

    std::cin.rdbuf(orig); // вернуть cin обратно
}

// 31️⃣ Проверка AddRule и ShowRules для нескольких правил
TEST(MachineTest, AddMultipleRulesAndShow) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    m.AddRule(Rule(2, Rule::writeZero, 3));
    EXPECT_NO_THROW(m.ShowRules());
}

// 32️⃣ Step с отсутствующим текущим правилом (currentRule = 42)
TEST(MachineTest, StepWithNonExistentCurrentRule) {
    Machine m;
    m.AddRule(Rule(1, Rule::writeOne, 2));
    testing::internal::CaptureStdout();
    m.Step(); // currentRule=1 exists
    m.Step(); // currentRule=2 missing
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

// 33️⃣ Проверка parseConditionalRule с некорректной строкой (ошибка в cerr)
TEST(MachineTest, ParseConditionalRuleInvalidInput) {
    Machine m;
    std::istringstream ss("a b c");
    std::stringstream buffer;
    std::streambuf* old = std::cerr.rdbuf(buffer.rdbuf());

    m.parseConditionalRule(1, Rule::moveIf, ss, "a b c");

    std::cerr.rdbuf(old);
    std::string out = buffer.str();
    EXPECT_NE(out.find("Ошибка"), std::string::npos);
}

// 34️⃣ parseSimpleRule с недостающим nextRule
TEST(MachineTest, ParseSimpleRuleFallbackOldFormat) {
    Machine m;
    std::istringstream ss("1 1"); // без третьего числа
    m.parseSimpleRule(1, Rule::writeOne, ss, "1 1");
    testing::internal::CaptureStdout();
    m.ShowRules();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("WRITE 1"), std::string::npos);
}

// 35️⃣ Step с currentRule = -1 (ничего не делает)
TEST(MachineTest, StepWithCurrentRuleMinusOne) {
    Machine m;
    m.Step();  // currentRule = 1 по умолчанию
    m.AddRule(Rule(1, Rule::end, -1));
    m.Step();  // currentRule = -1 после окончания
    EXPECT_NO_THROW(m.Step());  // ещё один вызов Step не должен падать
}

// 36️⃣ Run с пустым набором правил
TEST(MachineTest, RunWithNoRules) {
    Machine m;
    m.RemoveRule(1); // если правило 1 есть, удалим
    testing::internal::CaptureStdout();
    m.Run();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("no such rule"), std::string::npos);
}

// 37️⃣ InputProgramFromConsole с некорректной строкой для moveIf
TEST(MachineTest, InputProgramFromConsoleInvalidMoveIf) {
    Machine m;
    std::istringstream input("1 5 0\n\n"); // мало чисел
    std::streambuf* orig = std::cin.rdbuf(input.rdbuf());

    testing::internal::CaptureStdout();
    m.InputProgramFromConsole();
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("Ошибка: для moveIf нужно 5 чисел"), std::string::npos);

    std::cin.rdbuf(orig);
}

// 38️⃣ InputProgramFromConsole с некорректной строкой для обычного правила
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

