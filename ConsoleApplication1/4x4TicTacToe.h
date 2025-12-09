/**
 * @file 4x4TicTacToe.h
 * @brief Header file for a 4x4 Tic-Tac-Toe variant where players move existing pieces.
 */

#ifndef _4X4TICTACTOE_H
#define _4X4TICTACTOE_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class TicTacToe4x4_Board
 * @brief Represents a 4x4 board where the game mechanic involves moving pieces.
 * @details Unlike standard Tic-Tac-Toe, this board is pre-filled with pieces.
 * Players win by aligning 3 of their symbols, moving them one step at a time
 * to adjacent empty cells.
 */
class TicTacToe4x4_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol representing an empty cell on the board.

public:
    /**
     * @brief Constructor for the 4x4 Board.
     * @details Initializes the 4x4 grid and sets up the initial configuration of pieces
     * (X and O) on the first and last rows.
     */
    TicTacToe4x4_Board();

    /**
     * @brief Updates the board with a player's move.
     * @details Interprets the move's x and y coordinates as encoded source
     * and destination positions (e.g., x = src_row*10 + src_col).
     * Validates that the move is to an adjacent empty cell.
     * @param move Pointer to the Move object containing source and destination info.
     * @return true if the move was valid and executed, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks if the specified player has won.
     * @details Scans rows, columns, and diagonals for 3 consecutive symbols belonging to the player.
     * @param player Pointer to the player being checked.
     * @return true if the player has a winning formation, false otherwise.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks if the specified player has lost.
     * @details Not applicable in this variant as the game ends on a win or draw.
     * @return Always returns false.
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks if the game is a draw.
     * @details Determines if the move limit (100 moves) has been reached without a winner.
     * @param player Pointer to the player (unused in logic).
     * @return true if the game is a draw, false otherwise.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game is over.
     * @param player Pointer to the player.
     * @return true if there is a win or a draw, false otherwise.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class TicTacToe4x4_UI
 * @brief User Interface for the 4x4 Tic-Tac-Toe game.
 * @details Handles input/output specific to the 4x4 variant, including
 * parsing movement coordinates (From -> To).
 */
class TicTacToe4x4_UI : public UI<char> {
public:
    /**
     * @brief Constructor for the 4x4 UI.
     */
    TicTacToe4x4_UI();

    /**
     * @brief Destructor for the 4x4 UI.
     */
    ~TicTacToe4x4_UI() {};

    /**
     * @brief Creates a new player object.
     * @param name The name of the player.
     * @param symbol The symbol representing the player (e.g., 'X' or 'O').
     * @param type The type of player (Human or Computer).
     * @return Pointer to the newly created Player object.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Gets a move from the player.
     * @details For Human players, prompts for "From" and "To" coordinates.
     * For Computer players, calculates a random valid move for one of its pieces.
     * @param player Pointer to the player whose turn it is.
     * @return Pointer to a Move object containing the encoded move coordinates.
     */
    virtual Move<char>* get_move(Player<char>* player);

private:
    /** * @brief Caches computer piece locations to optimize AI move generation.
     */
    vector<pair<int, int>> computer_pieces;

    /** * @brief Flag to check if computer pieces have been tracked initially.
     */
    bool is_initialized = false;
};

#endif // _4X4TICTACTOE_H