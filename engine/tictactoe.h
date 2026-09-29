/**
 * @file tictactoe.h
 * @brief Tic-tac-toe rules and minimax AI. Board is 9 chars of 'X', 'O', '.'.
 */
#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <string>

namespace tictactoe
{

constexpr char k_empty = '.';

/**
 * @brief Winner of a board.
 * @param board 9-char board.
 * @return 'X' or 'O' if someone won, 'D' for draw, k_empty if still playing.
 */
char winner(const std::string &board);

/**
 * @brief Best move for a side using full minimax (9 cells, cheap).
 * @param board 9-char board, game not over.
 * @param side 'X' or 'O'.
 * @return Cell index 0-8. No side effects.
 */
int best_move(const std::string &board, char side);

} // namespace tictactoe

#endif // TICTACTOE_H
