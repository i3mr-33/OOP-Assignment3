/**
 * @file TicTacToe5x5_Classes.cpp
 * @brief Implementation of 5x5 Tic-Tac-Toe board and UI classes.
 *
 * This is a variant where the winner is determined by counting
 * 3-in-a-row patterns after 24 moves have been played.
 */

#include "TicTacToe5x5_Classes.h"
#include <cstdlib>
#include <ctime>

// ---------------- TicTacToe5x5_Board  Implementation ----------------

/**
 * @brief Constructor for 5x5 Tic-Tac-Toe board.
 * @details Initializes a 5x5 board with blank symbols ('.') and sets move count to zero.
 */
TicTacToe5x5_Board::TicTacToe5x5_Board()
    : Board<char>(5, 5)
{
    // Initialize all cells with blank symbol (default is '.')
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = blank_symbol;

    n_moves = 0;
}

/**
 * @brief Updates the board with a given move.
 * @param move Pointer to the Move object containing position and symbol.
 * @return true if the move was valid and executed, false otherwise.
 *
 * @note Move coordinates are (row, column) with 0-based indexing.
 */

bool TicTacToe5x5_Board::update_board(Move<char> *move)
{
    if (!move)
        return false;
    int x = move->get_x(); // row index
    int y = move->get_y(); // column index
    char s = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns)
    {
        cout << "Invalid position. Try again.\n";
        return false;
    }
    // Check if cell is empty
    if (board[x][y] != blank_symbol)
    {
        cout << "Cell already occupied. Try again.\n";
        return false;
    }
    // Place symbol and increment move counter
    board[x][y] = s;
    ++n_moves;
    return true;
}

/**
 * @brief Counts all occurrences of 3 consecutive symbols in a row for a given symbol.
 * @param sym The symbol to count (either 'X' or 'O').
 * @return Total count of 3-in-a-row patterns for the given symbol.
 *
 * @note Counts patterns in rows, columns, and both diagonals.
 * Overlapping patterns are counted separately.
 */
int TicTacToe5x5_Board::count_three_in_row(char sym) const
{
    int count = 0;
    // rows
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j <= columns - 3; ++j)
        {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i][j + k] != sym)
                {
                    ok = false;
                    break;
                }
            if (ok)
                ++count;
        }
    }
    // columns
    for (int j = 0; j < columns; ++j)
    {
        for (int i = 0; i <= rows - 3; ++i)
        {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j] != sym)
                {
                    ok = false;
                    break;
                }
            if (ok)
                ++count;
        }
    }
    // main diagonals (down-right)
    for (int i = 0; i <= rows - 3; ++i)
    {
        for (int j = 0; j <= columns - 3; ++j)
        {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j + k] != sym)
                {
                    ok = false;
                    break;
                }
            if (ok)
                ++count;
        }
    }
    // anti-diagonals (down-left)
    for (int i = 0; i <= rows - 3; ++i)
    {
        for (int j = 2; j < columns; ++j)
        {
            bool ok = true;
            for (int k = 0; k < 3; ++k)
                if (board[i + k][j - k] != sym)
                {
                    ok = false;
                    break;
                }
            if (ok)
                ++count;
        }
    }
    return count;
}

/**
 * @brief Determines if the given player has won the game.
 * @param player Pointer to the player object.
 * @return true if the player has more 3-in-a-row patterns than opponent, false otherwise.
 *
 * @note Game only has a winner after 24 moves have been played.
 * Win condition is based on comparing counts of 3-in-a-row patterns.
 */

bool TicTacToe5x5_Board::is_win(Player<char> *player)
{
    if (!player)
        return false;
    if (n_moves < 24)
        return false; // Game continues until 24 moves
    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X'; // opponent symbol:
    int a = count_three_in_row(sym);
    int b = count_three_in_row(other);
    return a > b;
}

/**
 * @brief Determines if the given player has lost the game.
 * @param player Pointer to the player object.
 * @return true if the player has fewer 3-in-a-row patterns than opponent, false otherwise.
 *
 * @note Game only has a loser after 24 moves have been played.
 */

bool TicTacToe5x5_Board::is_lose(Player<char> *player)
{
    if (!player)
        return false;
    if (n_moves < 24)
        return false;
    char sym = player->get_symbol();
    char other = (sym == 'X') ? 'O' : 'X';
    int a = count_three_in_row(sym);
    int b = count_three_in_row(other);
    return a < b;
}

/**
 * @brief Determines if the game ended in a draw.
 * @param player Unused parameter (kept for interface compatibility).
 * @return true if both players have equal number of 3-in-a-row patterns after 24 moves.
 */

bool TicTacToe5x5_Board::is_draw(Player<char> *player)
{
    (void)player;
    if (n_moves < 24)
        return false;
    int a = count_three_in_row('X');
    int b = count_three_in_row('O');
    return a == b;
}

/**
 * @brief Checks if the game is over.
 * @param player Unused parameter (kept for interface compatibility).
 * @return true if 24 or more moves have been played, false otherwise.
 */

bool TicTacToe5x5_Board::game_is_over(Player<char> *player)
{
    (void)player;
    return n_moves >= 24;
}

// ---------------- TicTacToe5x5_UI  Implementation ----------------

/**
 * @brief Constructor for 5x5 Tic-Tac-Toe UI.
 * @details Sets up the game UI with title and seed for random number generation.
 */

TicTacToe5x5_UI::TicTacToe5x5_UI()
    : UI<char>("FCAI 5x5 Tic-Tac-Toe", 2)
{
    // seed random for computer moves
    srand(static_cast<unsigned int>(time(nullptr)));
}

/**
 * @brief Creates a new player instance.
 * @param name Player's name.
 * @param symbol Player's symbol ('X' or 'O').
 * @param type Player type (HUMAN or COMPUTER).
 * @return Pointer to the newly created Player object.
 */

Player<char> *TicTacToe5x5_UI::create_player(string &name, char symbol, PlayerType type)
{
    // Use base Player class as in XO example
    Player<char> *p = new Player<char>(name, symbol, type);
    return p;
}

/**
 * @brief Gets a move from the player (human or computer).
 * @param player Pointer to the current player.
 * @return Pointer to the Move object containing the chosen move.
 *
 * @note For computer player: selects a random empty cell.
 * @note For human player: prompts for row and column input.
 * @warning Memory allocated for Move object must be freed by caller.
 */

Move<char> *TicTacToe5x5_UI::get_move(Player<char> *player)
{
    if (!player)
        return nullptr;

    if (player->get_type() == PlayerType::COMPUTER)
    {
        // generate random available cell
        Board<char> *b = player->get_board_ptr();
        if (!b)
            return nullptr;

        // Collect all empty positions
        vector<pair<int, int>> empties;
        auto mat = b->get_board_matrix();
        for (int i = 0; i < (int)mat.size(); ++i)
            for (int j = 0; j < (int)mat[0].size(); ++j)
                if (mat[i][j] == '.')
                    empties.emplace_back(i, j);

        if (empties.empty())
            return new Move<char>(0, 0, player->get_symbol()); // Fallback move

        // Select random empty cell
        int idx = std::rand() % empties.size();
        return new Move<char>(empties[idx].first, empties[idx].second, player->get_symbol());
    }
    else
    {
        // Get move from human player via console input
        int r, c;
        cout << player->get_name() << " (" << player->get_symbol() << ") enter row col: ";
        cin >> r >> c;
        return new Move<char>(r, c, player->get_symbol());
    }
}
