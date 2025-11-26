
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "4x4TicTacToe.h"
#include <vector>

using namespace std;


TicTacToe4x4_Board ::TicTacToe4x4_Board() : Board(4, 4) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;

    this->board[0][0] = 'O'; this->board[0][1] = 'X';
    this->board[0][2] = 'O'; this->board[0][3] = 'X';

    this->board[3][0] = 'X'; this->board[3][1] = 'O';
    this->board[3][2] = 'X'; this->board[3][3] = 'O';
    this->n_moves = 0;
}

bool TicTacToe4x4_Board::update_board(Move<char>* move) {
	int x = move->get_x();
	int y = move->get_y();
	char symbol = move->get_symbol();
    int src_r = x / 10;
    int src_c = x % 10;
    int dest_r = y / 10;
    int dest_c = y % 10;

    if(src_r < 0 || src_r >= 4 || src_c < 0 || src_c >= 4 ||
       dest_r < 0 || dest_r >= 4 || dest_c < 0 || dest_c >= 4)
		return false;

    if(board[src_r][src_c] != symbol) 
		return false;

    if (board[dest_r][dest_c] != blank_symbol)
    return false;

    int row_diff = abs(dest_r - src_r);
    int col_diff = abs(dest_c - src_c);
    if (row_diff + col_diff == 1)
    {
        board[dest_r][dest_c] = symbol;
        board[src_r][src_c] = blank_symbol;
        n_moves++;
        return true;
    }
	return false;
}

bool TicTacToe4x4_Board::is_win(Player<char>* player) {
    char sym = player->get_symbol();

    // Helper to check 3 cells
    auto check_3 = [&](char a, char b, char c) {
        return a == sym && b == sym && c == sym;
        };

   
    for (int i = 0; i < 4; i++) {
        if (check_3(board[i][0], board[i][1], board[i][2])) return true;
        if (check_3(board[i][1], board[i][2], board[i][3])) return true;
    }

    for (int i = 0; i < 4; i++) {
        if (check_3(board[0][i], board[1][i], board[2][i])) return true;
        if (check_3(board[1][i], board[2][i], board[3][i])) return true;
    }


    if (check_3(board[0][0], board[1][1], board[2][2])) return true;
    if (check_3(board[1][1], board[2][2], board[3][3])) return true;


    if (check_3(board[0][3], board[1][2], board[2][1])) return true;
    if (check_3(board[1][2], board[2][1], board[3][0])) return true;


    if (check_3(board[0][1], board[1][2], board[2][3])) return true; 
    if (check_3(board[1][0], board[2][1], board[3][2])) return true; 

    if (check_3(board[0][2], board[1][1], board[2][0])) return true; 
    if (check_3(board[1][3], board[2][2], board[3][1])) return true; 

    return false;
}

bool TicTacToe4x4_Board::is_draw(Player<char>* player) {
    return (n_moves == 16 && !is_win(player));
}

bool TicTacToe4x4_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}


TicTacToe4x4_UI::TicTacToe4x4_UI() : UI<char>("Weclome to FCAI 4x4 Tic-Tac-Toe", 3) {}

Player<char>* TicTacToe4x4_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* TicTacToe4x4_UI::get_move(Player<char>* player) {
    int x, y;
	int r1, c1, r2, c2;

    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nMove from (Row Column) (0-4): ";
        cin >> r1 >> c1;
        cout << "\nMove to (Row Column) (0-4): ";
        cin >> r2 >> c2;
		x = r1 * 10 + c1;
		y = r2 * 10 + c2;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        
    }
    return new Move<char>(x, y, player->get_symbol());
}
