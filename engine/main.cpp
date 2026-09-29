/**
 * @file main.cpp
 * @brief CLI: `ttt_engine <board>`. AI plays 'O', replies once, prints JSON
 * {"board":"...","winner":"."} to stdout. Exit 2 on invalid input.
 * And this is a test
 */
#include "tictactoe.h"

#include <iostream>
#include <string>

int main(const int argc, const char *const argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage: ttt_engine <9 chars of X, O, .>\n";
        return 2;
    }
    std::string board = argv[1];
    if (board.size() != 9 ||
        board.find_first_not_of("XO.") != std::string::npos)
    {
        std::cerr << "invalid board\n";
        return 2;
    }
    if (tictactoe::winner(board) == tictactoe::k_empty)
    {
        board[tictactoe::best_move(board, 'O')] = 'O';
    }
    std::cout << "{\"board\":\"" << board << "\",\"winner\":\""
              << tictactoe::winner(board) << "\"}\n";
    return 0;
}
