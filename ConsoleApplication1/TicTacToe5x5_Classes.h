/**
 * @file TicTacToe5x5_Classes.h
 * @brief Header file for 5x5 Tic-Tac-Toe game classes.
 *
 * This file defines the board and UI classes for a 5x5 Tic-Tac-Toe variant.
 * The game determines the winner by counting 3-in-a-row patterns after 24 moves.
 */

#ifndef TICTACTOE5X5_CLASSES_H
#define TICTACTOE5X5_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * @class TicTacToe5x5_Board
 * @brief Represents a 5x5 Tic-Tac-Toe game board.
 *
 * Inherits from the generic Board template class.
 * This variant uses a unique scoring system based on counting 3-in-a-row patterns.
 */
class TicTacToe5x5_Board : public Board<char>
{
private:
    char blank_symbol = '.'; // Character representing an empty cell

    /**
     * @brief Counts all occurrences of 3 consecutive symbols for a given player.
     * @param sym The symbol ('X' or 'O') to count patterns for.
     * @return Total number of 3-in-a-row segments for the given symbol.
     *
     * @note Searches in rows, columns, and both diagonal directions.
     * @note Overlapping patterns are counted separately.
     */
    int count_three_in_row(char sym) const;

public:
    TicTacToe5x5_Board();

    bool update_board(Move<char> *move) override;
    bool is_win(Player<char> *player) override;
    bool is_lose(Player<char> *player) override;
    bool is_draw(Player<char> *player) override;
    bool game_is_over(Player<char> *player) override;
    int get_score(char sym) const { return count_three_in_row(sym); };
};

/**
 * @class TicTacToe5x5_UI
 * @brief User Interface class for the 5x5 Tic-Tac-Toe game.
 *
 * Handles player creation and move input for both human and computer players.
 */

class TicTacToe5x5_UI : public UI<char>
{
public:
    TicTacToe5x5_UI();
    ~TicTacToe5x5_UI() {}

    Player<char> *create_player(string &name, char symbol, PlayerType type) override;
    Move<char> *get_move(Player<char> *player) override;
};

#endif // TICTACTOE5X5_CLASSES_H
