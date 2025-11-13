#ifndef NUMERICAL_TICTACTOE_CLASSES_H
#define NUMERICAL_TICTACTOE_CLASSES_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @class NumericalTicTacToe_Board
 * @brief Represents the Numerical Tic-Tac-Toe game board
 *
 * This is a 3x3 grid where Player 1 uses odd numbers (1,3,5,7,9)
 * and Player 2 uses even numbers (2,4,6,8). The goal is to make
 * a line (row, column, or diagonal) sum to 15.
 */
class NumericalTicTacToe_Board : public Board<int> {
private:
    vector<int> available_odds;  ///< Available odd numbers for Player 1
    vector<int> available_evens; ///< Available even numbers for Player 2

public:
    /**
     * @brief Constructor that initializes the 3x3 board
     */
    NumericalTicTacToe_Board();

    /**
     * @brief Updates the board with a player's move
     * @param move Pointer to a Move<int> object containing position and number
     * @return true if move is valid and applied, false otherwise
     */
    bool update_board(Move<int>* move);

    /**
     * @brief Checks if the given player has won
     * @param player Pointer to the player being checked
     * @return true if player has a winning line summing to 15
     */
    bool is_win(Player<int>* player);

    /**
     * @brief Checks if the given player has lost
     * @param player Pointer to the player being checked
     * @return Always returns false (not used in this game)
     */
    bool is_lose(Player<int>* player) { return false; }

    /**
     * @brief Checks if the game has ended in a draw
     * @param player Pointer to the player being checked
     * @return true if board is full and no player has won
     */
    bool is_draw(Player<int>* player);

    /**
     * @brief Checks if the game is over (win or draw)
     * @param player Pointer to the player to evaluate
     * @return true if game has ended
     */
    bool game_is_over(Player<int>* player);

    /**
     * @brief Checks if a number is available for the current player
     * @param number The number to check
     * @param is_player1 Whether checking for player 1 (odds) or player 2 (evens)
     * @return true if number is available
     */
    bool is_number_available(int number, bool is_player1);

    /**
     * @brief Gets available numbers for a player
     * @param is_player1 Whether to get odds (player1) or evens (player2)
     * @return Vector of available numbers
     */
    vector<int> get_available_numbers(bool is_player1) const;
};

//-----------------------------------------------------

/**
 * @class NumericalTicTacToe_UI
 * @brief User Interface for Numerical Tic-Tac-Toe game
 */
class NumericalTicTacToe_UI : public UI<int> {
public:
    /**
     * @brief Constructor
     */
    NumericalTicTacToe_UI();

    /**
     * @brief Creates a player for the game
     * @param name Player name
     * @param symbol Player symbol (1 for player1, 2 for player2)
     * @param type Player type (Human or Computer)
     * @return Pointer to created Player object
     */
    Player<int>* create_player(string& name, int symbol, PlayerType type);

    /**
     * @brief Gets a move from the player
     * @param player Pointer to the current player
     * @return Pointer to Move object representing the player's action
     */
    Move<int>* get_move(Player<int>* player);

    /**
     * @brief Sets up players for the game
     * @return Array of two Player pointers
     */
    Player<int>** setup_players();
};

#endif // NUMERICAL_TICTACTOE_CLASSES_H