/**
 * @file test_engine.cpp
 * @brief GoogleTest unit tests for tictactoe rules and AI.
 */
#include "tictactoe.h"

#include <gtest/gtest.h>

TEST(Winner, DetectsRowWin)
{
    // Arrange / Act / Assert: pure function, one line each.
    EXPECT_EQ(tictactoe::winner("XXX.OO..."), 'X');
}

TEST(Winner, DetectsDraw)
{
    EXPECT_EQ(tictactoe::winner("XOXXOOOXX"), 'D');
}

TEST(Winner, EmptyBoardInProgress)
{
    EXPECT_EQ(tictactoe::winner("........."), tictactoe::k_empty);
}

TEST(BestMove, TakesWin)
{
    EXPECT_EQ(tictactoe::best_move("XX.OO....", 'O'), 5);
}

TEST(BestMove, BlocksLoss)
{
    EXPECT_EQ(tictactoe::best_move("XX..O....", 'O'), 2);
}
