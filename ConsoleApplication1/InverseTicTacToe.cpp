//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <limits>  // for input validation
#include "InverseTicTacToe.h"

using namespace std;

InverseTicTacToe_Board::InverseTicTacToe_Board() : Board(3, 3) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool InverseTicTacToe_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate coordinates
    if (x < 0 || x >= rows || y < 0 || y >= columns) {
        cout << "Invalid position! Coordinates must be within board limits (0-2).\n";
        return false;
    }

    // Check if cell is empty
    if (mark != 0 && board[x][y] != blank_symbol) {
        cout << "Cell is occupied!\n";
        return false;
    }

    if (mark == 0) { // Undo move
        if (board[x][y] != blank_symbol) {
            n_moves--;
            board[x][y] = blank_symbol;
            return true;
        }
        cout << "Cannot undo - cell is already empty!\n";
        return false;
    }
    else {         // Apply move
        if (board[x][y] == blank_symbol) {
            n_moves++;
            board[x][y] = toupper(mark);
            return true;
        }
        cout << "Cell is occupied!\n";
        return false;
    }
}

bool InverseTicTacToe_Board::is_lose(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    // Check rows and columns
    for (int i = 0; i < rows; ++i) {
        if ((all_equal(board[i][0], board[i][1], board[i][2]) && board[i][0] == sym) ||
            (all_equal(board[0][i], board[1][i], board[2][i]) && board[0][i] == sym))
            return true;
    }

    // Check diagonals
    if ((all_equal(board[0][0], board[1][1], board[2][2]) && board[1][1] == sym) ||
        (all_equal(board[0][2], board[1][1], board[2][0]) && board[1][1] == sym))
        return true;

    return false;
}

bool InverseTicTacToe_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool InverseTicTacToe_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- XO_UI Implementation

InverseTicTacToe_UI::InverseTicTacToe_UI() : UI<char>("Welcome to Inverse Tic - Tac - Toe Game!", 3) {}

Player<char>* InverseTicTacToe_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* InverseTicTacToe_UI::get_move(Player<char>* player) {
    int x, y;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x and y (0 to 2): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
