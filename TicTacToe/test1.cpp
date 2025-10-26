/**
 * @file test1.cpp
 * @brief Unit тесты.
 * @details
 * Этот файл содержит 30 Unit тестов и дополнительные функции для их реализации.
 * Покрытие тестами составляет 86% строк файла Play.cpp.
 *
 * @author Ekatsune
 * @see Play
 */

#include <gtest/gtest.h>
#include "Play.h"
#include <iostream>

void fillRow(Play& g, int row, char sym) {
    for (int c = 0; c < g[row].size(); ++c)
        g[row][c] = sym;
}
void fillCol(Play& g, int col, char sym) {
    for (int r = 0; r < g[col].size(); ++r)
        g[r][col] = sym;
}
void fillMainDiag(Play& g, char sym) {
    for (int i = 0; i < g[0].size(); ++i)
        g[i][i] = sym;
}
void fillAntiDiag(Play& g, char sym) {
    int n = g[0].size();
    for (int i = 0; i < n; ++i)
        g[i][n - 1 - i] = sym;
}

TEST(PlayConstructorTest, DefaultSizeIs3) {
    Play g;
    EXPECT_EQ(g[0].size(), 3);
}

TEST(PlayConstructorTest, CustomSizeIsApplied) {
    Play g(5);
    EXPECT_EQ(g[0].size(), 5);
}

TEST(PlayConstructorTest, EmptyFieldInitializedWithStars) {
    Play g(4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            EXPECT_EQ(g[i][j], '*');
}

// =============================
// 2. Оператор []
// =============================
TEST(PlayOperatorTest, CanAccessAndModifyCell) {
    Play g(3);
    g[1][2] = 'X';
    EXPECT_EQ(g[1][2], 'X');
}

TEST(PlayOperatorTest, ConstAccessWorksCorrectly) {
    Play g(3);
    g[0][0] = 'O';
    const Play& cg = g;
    EXPECT_EQ(cg[0][0], 'O');
}

TEST(PlayOperatorTest, SeparateRowsIndependent) {
    Play g(3);
    g[0][0] = 'X';
    EXPECT_EQ(g[1][0], '*');
}

TEST(PlayWinTest, DetectsRowWinViaAreWin) {
    Play g(3);
    fillRow(g, 0, 'X');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayWinTest, DetectsColumnWinViaAreWin) {
    Play g(3);
    fillCol(g, 1, 'O');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayWinTest, DetectsMainDiagonalWinViaAreWin) {
    Play g(3);
    fillMainDiag(g, 'X');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayWinTest, DetectsAntiDiagonalWinViaAreWin) {
    Play g(3);
    fillAntiDiag(g, 'O');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayWinTest, NoWinWhenBoardEmpty) {
    Play g(3);
    g.AreWin();
    EXPECT_FALSE(g.GetGameOver());
}

TEST(PlayDrawTest, DetectsDrawWhenFullAndNoWin) {
    Play g(3);
    const char pattern[3][3] = {
            {'X', 'O', 'X'},
            {'O', 'O', 'X'},
            {'X', 'X', 'O'}
    };
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g[i][j] = pattern[i][j];
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayDrawTest, NotDrawWhenEmptyCellsExist) {
    Play g(3);
    g[0][0] = 'X';
    g.AreWin();
    EXPECT_FALSE(g.GetGameOver());
}

TEST(PlaySizeTest, SupportsOneByOneBoard) {
    Play g(1);
    g[0][0] = 'X';
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlaySizeTest, SupportsLargeBoard) {
    Play g(10);
    EXPECT_EQ(g[9].size(), 10);
}

TEST(PlaySizeTest, InitializesAllCellsEmpty) {
    Play g(5);
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            EXPECT_EQ(g[i][j], '*');
}

TEST(PlayAreWinTest, AreWinSetsGameOverTrueAfterRowWin) {
    Play g(3);
    fillRow(g, 1, 'O');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayAreWinTest, AreWinDoesNotChangeGameOverIfNoWin) {
    Play g(3);
    g.AreWin();
    EXPECT_FALSE(g.GetGameOver());
}

TEST(PlayAreWinTest, AreWinHandlesFullDraw) {
    Play g(3);
    const char pattern[3][3] = {
            {'X', 'O', 'X'},
            {'O', 'O', 'X'},
            {'X', 'X', 'O'}
    };
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            g[i][j] = pattern[i][j];
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayGameOverTest, GameOverInitiallyFalse) {
    Play g(3);
    EXPECT_FALSE(g.GetGameOver());
}

TEST(PlayGameOverTest, GameOverAfterWinTrue) {
    Play g(3);
    fillRow(g, 0, 'X');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayGameOverTest, GameOverRemainsTrueAfterSet) {
    Play g(3);
    fillRow(g, 0, 'X');
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
    g.AreWin();
    EXPECT_TRUE(g.GetGameOver());
}

TEST(PlayFieldTest, ModifyingOneCellDoesNotAffectOthers) {
    Play g(3);
    g[0][0] = 'X';
    EXPECT_EQ(g[1][1], '*');
}

TEST(PlayFieldTest, EmptyFieldSymbolIsStar) {
    Play g(3);
    EXPECT_EQ(g[2][2], '*');
}

TEST(PlayFieldTest, ChangesPersistBetweenCalls) {
    Play g(3);
    g[0][0] = 'X';
    EXPECT_EQ(g[0][0], 'X');
}

TEST(PlayBoundsTest, CanAccessLastCell) {
    Play g(4);
    g[3][3] = 'O';
    EXPECT_EQ(g[3][3], 'O');
}

TEST(PlayBoundsTest, AccessZeroIndexWorks) {
    Play g(3);
    g[0][0] = 'X';
    EXPECT_EQ(g[0][0], 'X');
}

TEST(PlayStabilityTest, AreWinDoesNotThrowOnLargeBoard) {
    Play g(20);
    EXPECT_NO_THROW(g.AreWin());
}

TEST(PlayStabilityTest, CanHandleMixedSymbols) {
    Play g(3);
    g[0][0] = 'X'; g[0][1] = 'O'; g[0][2] = '*';
    EXPECT_NO_THROW(g.AreWin());
}

TEST(PlayStabilityTest, MultipleCallsSafe) {
    Play g(3);
    EXPECT_NO_THROW({
                        for (int i = 0; i < 10; ++i)
                            g.AreWin();
                    });
}
