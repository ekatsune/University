#include "../all.hpp"
#include <sstream>
#include <gtest/gtest.h>
/**
 * @file tests.cpp
 * @brief Unit тесты.
 * @details
 * Этот файл содержит.
 * Покрытие тестами составляет 95% строк файла Machine.cpp,
 * 90% - Rule.cpp, 94% - Tape.cpp.
 *
 * @author Ekatsune
 * @see all
 */

// Тест конструктора и операторов сложения/вычитания
TEST(BYNTest, ArithmeticOperators) {
BYN a(150); // 1.50 BYN
BYN b(75);  // 0.75 BYN

BYN sum = a + b;
BYN diff = a - b;

EXPECT_EQ(sum.GetRubles(), 2);
EXPECT_EQ(sum.GetKopecks(), 25);

EXPECT_EQ(diff.GetRubles(), 0);
EXPECT_EQ(diff.GetKopecks(), 75);

a += b;
EXPECT_EQ(a.GetRubles(), 2);
EXPECT_EQ(a.GetKopecks(), 25);

a -= b;
EXPECT_EQ(a.GetRubles(), 1);
EXPECT_EQ(a.GetKopecks(), 50);
}

// Тест операторов сравнения
TEST(BYNTest, ComparisonOperators) {
BYN a(100);
BYN b(200);

EXPECT_TRUE(a < b);
EXPECT_TRUE(b > a);
EXPECT_TRUE(a <= b);
EXPECT_TRUE(b >= a);
EXPECT_TRUE(a != b);
EXPECT_FALSE(a == b);

BYN c(100);
EXPECT_TRUE(a == c);
EXPECT_FALSE(a != c);
}

// Тест операторов умножения и деления
TEST(BYNTest, MultiplyDivide) {
BYN a(100); // 1.00 BYN

BYN b = a * 2.5;
EXPECT_EQ(b.GetRubles(), 2);
EXPECT_EQ(b.GetKopecks(), 50);

BYN c = b / 2.0;
EXPECT_EQ(c.GetRubles(), 1);
EXPECT_EQ(c.GetKopecks(), 25);
}

// Тест потокового вывода
TEST(BYNTest, OutputOperator) {
BYN a(123); // 1.23 BYN
std::ostringstream os;
os << a;
EXPECT_EQ(os.str(), "1,23 BYN");

BYN b(5); // 0.05 BYN
std::ostringstream os2;
os2 << b;
EXPECT_EQ(os2.str(), "0,05 BYN");
}

// Тест потокового ввода
TEST(BYNTest, InputOperator) {
BYN a(0);
std::istringstream is("1.50");
is >> a;
EXPECT_EQ(a.GetRubles(), 1);
EXPECT_EQ(a.GetKopecks(), 50);

BYN b(0);
std::istringstream is2("2,75");
is2 >> b;
EXPECT_EQ(b.GetRubles(), 2);
EXPECT_EQ(b.GetKopecks(), 75);

// Неправильный ввод
BYN c(0);
std::istringstream is3("abc");
is3 >> c;
EXPECT_TRUE(is3.fail());
}

// Тест на нули и отрицательные значения
TEST(BYNTest, ZeroAndNegative) {
BYN zero(0);
EXPECT_EQ(zero.GetRubles(), 0);
EXPECT_EQ(zero.GetKopecks(), 0);

BYN neg(-250); // -2.50 BYN
EXPECT_EQ(neg.GetRubles(), -2);
EXPECT_EQ(neg.GetKopecks(), -50);
}
