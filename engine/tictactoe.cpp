/**
 * @file tictactoe.cpp
 * @brief Tic-tac-toe rules and minimax AI.
 */
#include "tictactoe.h"

namespace tictactoe
{

namespace
{

constexpr int k_lines[8][3] = {
    {0, 1, 2},
    {3, 4, 5},
    {6, 7, 8},
    {0, 3, 6},
    {1, 4, 7},
    {2, 5, 8},
    {0, 4, 8},
    {2, 4, 6}};

char other(const char side)
{
    return side == 'X' ? 'O' : 'X';
}

/** Score from `side`'s view: +10 win, -10 loss, 0 draw; depth prefers fast
 * wins. */
int minimax(std::string &board, const char side, const int depth)
{
    const char w = winner(board);
    if (w == 'D')
    {
        return 0;
    }
    if (w != k_empty)
    {
        return w == side ? 10 - depth : depth - 10;
    }
    int best = -100;
    for (char &cell : board)
    {
        if (cell != k_empty)
        {
            continue;
        }
        cell = side;
        const int score = -minimax(board, other(side), depth + 1);
        cell = k_empty;
        best = score > best ? score : best;
    }
    return best;
}

} // namespace

char winner(const std::string &board)
{
    for (const auto &line : k_lines)
    {
        const char c = board[line[0]];
        if (c != k_empty && c == board[line[1]] && c == board[line[2]])
        {
            return c;
        }
    }
    return board.find(k_empty) == std::string::npos ? 'D' : k_empty;
}

int best_move(const std::string &board, const char side)
{
    std::string work = board;
    int best_score = -100;
    int best_cell = -1;
    for (int i = 0; i < 9; ++i)
    {
        if (work[i] != k_empty)
        {
            continue;
        }
        work[i] = side;
        const int score = -minimax(work, other(side), 1);
        work[i] = k_empty;
        if (score > best_score)
        {
            best_score = score;
            best_cell = i;
        }
    }
    return best_cell;
}

} // namespace tictactoe
