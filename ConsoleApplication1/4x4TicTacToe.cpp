/**
 * @file 4x4TicTacToe.cpp
 * @brief Implementation of the 4x4 Tic-Tac-Toe variant.
 */

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "4x4TicTacToe.h"
#include <vector>

using namespace std;

/**
 * @brief Constructor: Sets up the board with initial pieces.
 * @details
 * Row 0 is filled with O X O X.
 * Row 3 is filled with X O X O.
 * The middle rows are empty.
 */
TicTacToe4x4_Board::TicTacToe4x4_Board() : Board(4, 4) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    // Set initial configuration
    this->board[0][0] = 'O'; this->board[0][1] = 'X';
    this->board[0][2] = 'O'; this->board[0][3] = 'X';

    this->board[3][0] = 'X'; this->board[3][1] = 'O';
    this->board[3][2] = 'X'; this->board[3][3] = 'O';
    this->n_moves = 0;
}

/**
 * @brief Executes a move by shifting a piece from one cell to another.
 * @details
 * 1. Decodes `move->get_x()` and `move->get_y()` to get source and destination coordinates.
 * - x holds source (row, col) as `row*10 + col`.
 * - y holds destination (row, col) as `row*10 + col`.
 * 2. Validates boundaries.
 * 3. Verifies ownership of the piece at source.
 * 4. Ensures destination is empty.
 * 5. Checks if the destination is adjacent (up, down, left, right).
 * * @param move The move object containing encoded source and destination.
 * @return true if the move is valid and executed.
 */
bool TicTacToe4x4_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Decode coordinates
    int src_r = x / 10;
    int src_c = x % 10;
    int dest_r = y / 10;
    int dest_c = y % 10;

    // Boundary Check
    if (src_r < 0 || src_r >= 4 || src_c < 0 || src_c >= 4 ||
        dest_r < 0 || dest_r >= 4 || dest_c < 0 || dest_c >= 4)
    {
        cout << "Move out of bounds!\n";
        return false;
    }

    // Check if player owns the source piece
    if (board[src_r][src_c] != symbol)
    {
		cout << "Source cell does not contain your piece!\n";
        return false;
    }

    // Check if destination is empty
    if (board[dest_r][dest_c] != blank_symbol)
    {
		cout << "Destination cell is not empty!\n";
        return false;
    }
    

    // Check Adjacency (must be 1 step orthogonal)
    int row_diff = abs(dest_r - src_r);
    int col_diff = abs(dest_c - src_c);
    if (row_diff + col_diff == 1)
    {
        board[dest_r][dest_c] = symbol;
        board[src_r][src_c] = blank_symbol;
        n_moves++;
        return true;
    }
	cout << "Destination cell is not adjacent!\n";
    return false;
}

/**
 * @brief Checks for a win condition (3 consecutive symbols).
 * @details Scans for 3 matching symbols in rows, columns, and diagonals.
 * Note: While the board is 4x4, the win condition logic here checks for 3 adjacent symbols.
 * @param player The player to check.
 * @return true if the player has 3 aligned pieces.
 */
bool TicTacToe4x4_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Helper to check 3 cells
    auto check_3 = [&](char a, char b, char c) {
        return a == sym && b == sym && c == sym;
        };

    // Check Rows (sliding window of 3)
    for (int i = 0; i < 4; i++) {
        if (check_3(board[i][0], board[i][1], board[i][2])) return true;
        if (check_3(board[i][1], board[i][2], board[i][3])) return true;
    }

    // Check Columns (sliding window of 3)
    for (int i = 0; i < 4; i++) {
        if (check_3(board[0][i], board[1][i], board[2][i])) return true;
        if (check_3(board[1][i], board[2][i], board[3][i])) return true;
    }

    // Check Main Diagonals
    if (check_3(board[0][0], board[1][1], board[2][2])) return true;
    if (check_3(board[1][1], board[2][2], board[3][3])) return true;

    // Check Anti-Diagonals
    if (check_3(board[0][3], board[1][2], board[2][1])) return true;
    if (check_3(board[1][2], board[2][1], board[3][0])) return true;

    // Check smaller diagonals
    if (check_3(board[0][1], board[1][2], board[2][3])) return true;
    if (check_3(board[1][0], board[2][1], board[3][2])) return true;

    if (check_3(board[0][2], board[1][1], board[2][0])) return true;
    if (check_3(board[1][3], board[2][2], board[3][1])) return true;

    return false;
}

/**
 * @brief Checks if the game is a draw.
 * @details A draw is declared if 100 moves have passed without a winner to prevent infinite loops.
 * @param player Unused.
 * @return true if move count reaches 100.
 */
bool TicTacToe4x4_Board::is_draw(Player<char>* player) {
    return (n_moves == 100 && !is_win(player));
}

bool TicTacToe4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


TicTacToe4x4_UI::TicTacToe4x4_UI() : UI<char>("Weclome to FCAI 4x4 Tic-Tac-Toe", 3) {}

Player<char>* TicTacToe4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

/**
 * @brief Captures the move from the player.
 * @details
 * - **Human**: Asks for `(r1, c1)` [From] and `(r2, c2)` [To]. Packs them into `x` and `y` integers.
 * - **Computer**:
 * 1. Initializes piece tracking if not already done.
 * 2. Randomly selects one of its pieces.
 * 3. Attempts to move it to a random adjacent valid spot.
 * 4. Updates internal piece tracking.
 * @param player The current player.
 * @return Move object with `x` containing encoded source (r1*10+c1) and `y` containing encoded dest (r2*10+c2).
 */
Move<char>* TicTacToe4x4_UI::get_move(Player<char>* player) {
    int x, y;
    int r1, c1, r2, c2;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nMove from (Row Column) (0-4): ";
        cin >> r1 >> c1;
        cout << "\nMove to (Row Column) (0-4): ";
        cin >> r2 >> c2;
        // Encode coordinates
        x = r1 * 10 + c1;
        y = r2 * 10 + c2;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        // Initialization of AI piece tracking
        if (!is_initialized) {
            char sym = player->get_symbol();
            computer_pieces.clear();

            if (sym == 'O') {
                computer_pieces.push_back({ 0, 0 });
                computer_pieces.push_back({ 0, 2 });
                computer_pieces.push_back({ 3, 1 });
                computer_pieces.push_back({ 3, 3 });
            }
            else {
                computer_pieces.push_back({ 0, 1 });
                computer_pieces.push_back({ 0, 3 });
                computer_pieces.push_back({ 3, 0 });
                computer_pieces.push_back({ 3, 2 });
            }
            is_initialized = true;
        }

        unsigned seed = rand();
        bool valid_move_found = false;

        // Try to find a valid move
        while (!valid_move_found) {
            int piece_index = rand() % computer_pieces.size();
            r1 = computer_pieces[piece_index].first;
            c1 = computer_pieces[piece_index].second;

            // Directions: Up, Down, Left, Right
            int dr[] = { -1, 1, 0, 0 };
            int dc[] = { 0, 0, -1, 1 };
            vector<int> dirs = { 0, 1, 2, 3 };

            // Shuffle directions for randomness
            for (int k = 0; k < dirs.size(); k++) {
                int r = rand() % dirs.size();
                swap(dirs[k], dirs[r]);
            }

            for (int i : dirs) {
                int test_r = r1 + dr[i];
                int test_c = c1 + dc[i];

                // Check bounds (actual validity checked by board update, but we pre-check bounds)
                if (test_r >= 0 && test_r < 4 && test_c >= 0 && test_c < 4) {
                    r2 = test_r;
                    c2 = test_c;

                    computer_pieces[piece_index] = { r2, c2 };

                    valid_move_found = true;
                    break;
                }
            }
        }

        cout << "Computer moves from (" << r1 << "," << c1 << ") to (" << r2 << "," << c2 << ")\n";
        x = r1 * 10 + c1;
        y = r2 * 10 + c2;
    }
    return new Move<char>(x, y, player->get_symbol());
}