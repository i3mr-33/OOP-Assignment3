/**
 * @file PyramidXO_Classes.cpp
 * @brief Implementation of the Pyramid Tic-Tac-Toe classes.
 */

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "PyramidXO_Classes.h"

using namespace std;

//--------------------------------------- PyramidX_O_Board Implementation

/**
 * @brief Constructor: Initializes a 3x5 board with blank symbols.
 */
PyramidX_O_Board::PyramidX_O_Board() : Board(3, 5) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

/**
 * @brief Updates the board state with the player's move.
 * @details Checks boundary conditions specific to the pyramid shape:
 * - Row 0: Only col 2 is valid.
 * - Row 1: Cols 1-3 are valid.
 * - Row 2: All cols 0-4 are valid.
 * Also handles undo logic if the mark passed is 0.
 * @param move The move containing coordinates (x, y) and the player's symbol.
 * @return true if the move was successfully placed (or undone), false if invalid.
 */
bool PyramidX_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Coordinates out of board limits.\n";
        return false;
    }
    // Pyramid geometry validation
    if (x == 0 && y != 2) {
        cout << "Invalid position! First row only allows middle cell (0,2).\n";
        return false;
    }
    if (x == 1 && (y < 1 || y > 3)) {
        cout << "Invalid position! Second row only allows columns 1-3.\n";
        return false;
    }
    // Occupancy check
    if (mark != 0 && board[x][y] != blank_symbol) {
        cout << "Cell is occupied!\n";
        return false;
    }

        if (board[x][y] == blank_symbol) {
            n_moves++;
            board[x][y] = toupper(mark);
            return true;
        }
        cout << "Cell is occupied!\n";
        return false;
}

/**
 * @brief Checks if the player has formed a winning line.
 * @details Verifies horizontal lines, the vertical central line, and diagonals.
 * @param player The player to check for a win.
 * @return true if a winning pattern is found.
 */
bool PyramidX_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    // Lambda to check 3 consecutive cells
    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Vertical win (Column 2)
    if (all_equal(board[0][2], board[1][2], board[2][2]) && board[0][2] == sym) return true;

    // Horizontal win (Row 1)
    if (all_equal(board[1][1], board[1][2], board[1][3]) && board[1][1] == sym) return true;

    // Horizontal wins (Row 2)
    if (all_equal(board[2][0], board[2][1], board[2][2]) && board[2][0] == sym) return true;
    if (all_equal(board[2][1], board[2][2], board[2][3]) && board[2][1] == sym) return true;
    if (all_equal(board[2][2], board[2][3], board[2][4]) && board[2][2] == sym) return true;

    // Diagonal wins
    if (all_equal(board[0][2], board[1][1], board[2][0]) && board[0][2] == sym) return true;
    if (all_equal(board[0][2], board[1][3], board[2][4]) && board[0][2] == sym) return true;
    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @param player The player context (unused).
 * @return true if 9 moves have been made and no winner exists.
 */
bool PyramidX_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

/**
 * @brief General game over check.
 * @param player The player context.
 * @return true if win or draw.
 */
bool PyramidX_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- pyramidXO_UI Implementation

PyramidXO_UI::PyramidXO_UI() : UI<char>("Weclome to FCAI Pyramid Tic-Tac-Toe", 3) {}

Player<char>* PyramidXO_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Retrieves input for the next move.
 * @details For humans, reads x and y from standard input. For computers, picks random coordinates.
 * @param player The player whose turn it is.
 * @return A new Move object with the chosen coordinates.
 */
Move<char>* PyramidXO_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x (0 to 2) and y (0 to 4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Random move generation for AI (Naive implementation)
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}

/**
 * @brief Renders the board to the console with pyramid indentation.
 * @param board The game board matrix.
 */
void PyramidXO_UI::display_board_matrix(const vector<vector<char>>& board) const {
    cout << "\n----------------------------\n\n";
    cout << "    0    1    2    3    4  ";
    cout << "\n            -----\n";
    for (int i = 0; i < 3; i++)
    {
        string padding = "";
        // Adjust padding to create pyramid shape
        if (i == 0) padding = "          ";
        if (i == 1) padding = "     ";
        cout << i << " ";
        cout << padding;

        for (int j = 0; j < 5; j++)
        {
            bool isValid = false;
            // Only print valid cells for the current row
            if (i == 0 && j == 2) isValid = true;
            else if (i == 1 && (j >= 1 && j <= 3)) isValid = true;
            else if (i == 2) isValid = true;

            if (isValid)
            {
                char cellValue = board[i][j];
                if (cellValue == 0) cellValue = '.';
                cout << "| " << cellValue << " |";
            }
        }
        // Draw separators matching the width of the row
        if (i == 0)
            cout << "\n            -----\n";
        if (i == 1)
            cout << "\n       ---------------\n";
        if (i == 2)
            cout << "\n  -------------------------\n";

    }
    cout << "\n\n----------------------------\n";
}