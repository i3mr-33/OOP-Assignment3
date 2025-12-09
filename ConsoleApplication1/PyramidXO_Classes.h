/**
 * @file PyramidXO_Classes.h
 * @brief Header file for the Pyramid Tic-Tac-Toe game.
 * @details Defines a board that is logically a 3x5 matrix but visually restricts
 * valid cells to form a pyramid shape.
 */

#ifndef PyramidXO_CLASSES_H
#define PyramidXO_CLASSES_H

#include "BoardGame_Classes.h"
using namespace std;

/**
 * @class PyramidX_O_Board
 * @brief Logic for the Pyramid-shaped Tic-Tac-Toe board.
 * @details
 * Row 0: 1 cell (index 2)
 * Row 1: 3 cells (indices 1, 2, 3)
 * Row 2: 5 cells (indices 0, 1, 2, 3, 4)
 */
class PyramidX_O_Board : public Board<char> {
private:
    char blank_symbol = '.'; ///< Symbol for empty slots.

public:
    /**
     * @brief Constructor initializes a 3x5 board and sets valid pyramid cells.
     */
    PyramidX_O_Board();

    /**
     * @brief Validates and applies a move to the pyramid board.
     * @details Ensures the move is within the "valid" pyramid cells and not just
     * anywhere in the 3x5 matrix. Also handles move counting.
     * @param move Pointer to the Move object.
     * @return true if the move is valid and applied, false otherwise.
     */
    bool update_board(Move<char>* move);

    /**
     * @brief Checks for a winning condition.
     * @details Checks horizontal, vertical, and diagonal lines specific to the pyramid geometry.
     * @param player Pointer to the player to check.
     * @return true if the player has won.
     */
    bool is_win(Player<char>* player);

    /**
     * @brief Checks for a losing condition.
     * @return Always false (standard XO rules).
     */
    bool is_lose(Player<char>*) { return false; };

    /**
     * @brief Checks for a draw.
     * @details A draw occurs if 9 moves are made (board full) with no winner.
     * @param player Pointer to the player.
     * @return true if the game is a draw.
     */
    bool is_draw(Player<char>* player);

    /**
     * @brief Checks if the game has ended.
     * @param player Pointer to the player.
     * @return true if won or drawn.
     */
    bool game_is_over(Player<char>* player);
};

/**
 * @class PyramidXO_UI
 * @brief User Interface specific to the Pyramid Tic-Tac-Toe.
 */
class PyramidXO_UI : public UI<char> {
public:
    /**
     * @brief Constructor for the Pyramid UI.
     */
    PyramidXO_UI();
    ~PyramidXO_UI() {};

    /**
     * @brief Creates a Human or Computer player.
     * @param name Name of the player.
     * @param symbol Symbol for the player.
     * @param type PlayerType (Human/Computer).
     * @return Pointer to the new Player instance.
     */
    Player<char>* create_player(string& name, char symbol, PlayerType type);

    /**
     * @brief Captures the desired move from the player.
     * @details Prompts user for coordinates or generates random coordinates for AI.
     * @param player Pointer to the player.
     * @return Pointer to the Move object.
     */
    virtual Move<char>* get_move(Player<char>* player);

    /** * @brief Displays the board formatted as a pyramid.
     * @details Overrides the generic display to print proper spacing and
     * only show valid cells of the pyramid structure.
     * @param board The 2D vector representing the game state.
     */
    void display_board_matrix(const vector<vector<char>>& board) const override;
};

#endif // PyramidXO_CLASSES_H