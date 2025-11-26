//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include "PyramidXO_Classes.h"

using namespace std;

//--------------------------------------- PyramidX_O_Board Implementation

PyramidX_O_Board::PyramidX_O_Board() : Board(3, 5) {
    // Initialize all cells with blank_symbol
    for (auto& row : board)
        for (auto& cell : row)
            cell = blank_symbol;
}

bool PyramidX_O_Board::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char mark = move->get_symbol();

    // Validate move and apply if valid
    if (!(x < 0 || x >= rows || y < 0 || y >= columns) &&
        (board[x][y] == blank_symbol || mark == 0)) {

		if (x == 0 && y != 2) return false; // First row, only middle cell allowed
		if (x == 1 && (y < 1 || y > 3)) return false; // Second row, only middle three cells allowed
        if (mark == 0) { // Undo move
            n_moves--;
            board[x][y] = blank_symbol;
        }
        else {         // Apply move
            n_moves++;
            board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

bool PyramidX_O_Board::is_win(Player<char>* player) {
    const char sym = player->get_symbol();

    auto all_equal = [&](char a, char b, char c) {
        return a == b && b == c && a != blank_symbol;
        };

    if (all_equal(board[0][2], board[1][2], board[2][2]) && board[0][2] == sym) return true;
   
    if (all_equal(board[1][1], board[1][2], board[1][3]) && board[1][1] == sym) return true;

    if (all_equal(board[2][0], board[2][1], board[2][2]) && board[2][0] == sym) return true;
    if (all_equal(board[2][1], board[2][2], board[2][3]) && board[2][1] == sym) return true;
    if (all_equal(board[2][2], board[2][3], board[2][4]) && board[2][2] == sym) return true;

    if (all_equal(board[0][2], board[1][1], board[2][0]) && board[0][2] == sym) return true;
    if (all_equal(board[0][2], board[1][3], board[2][4]) && board[0][2] == sym) return true; 
    return false;
}

bool PyramidX_O_Board::is_draw(Player<char>* player) {
    return (n_moves == 9 && !is_win(player));
}

bool PyramidX_O_Board::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

//--------------------------------------- pyramidXO_UI Implementation

PyramidXO_UI::PyramidXO_UI() : UI<char>("Weclome to FCAI Pyramid Tic-Tac-Toe", 3) {}

Player<char>* PyramidXO_UI::create_player(string& name, char symbol, PlayerType type) {
    // Create player based on type
    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
        << " player: " << name << " (" << symbol << ")\n";

    return new Player<char>(name, symbol, type);
}

Move<char>* PyramidXO_UI::get_move(Player<char>* player) {
    int x, y;
    
    if (player->get_type() == PlayerType::HUMAN) {
        cout << "\nPlease enter your move x (0 to 2) and y (0 to 4): ";
        cin >> x >> y;
    }
    else if (player->get_type() == PlayerType::COMPUTER) {
        x = rand() % player->get_board_ptr()->get_rows();
        y = rand() % player->get_board_ptr()->get_columns();
    }
    return new Move<char>(x, y, player->get_symbol());
}
void PyramidXO_UI::display_board_matrix(const vector<vector<char>>& board) const {
    cout << "\n----------------------------\n\n";
    cout << "    0    1    2    3    4  ";
    cout << "\n            -----\n";
    for (int i = 0; i < 3; i++)
    {
		string padding = "";
		if (i == 0) padding = "          ";
		if (i == 1) padding = "     ";
        cout << i << " ";
        cout << padding;

        for (int j = 0; j < 5; j++)
        {
            
			bool isValid = false;
			if (i == 0 && j == 2) isValid = true;
            else if(i == 1 && (j >= 1 && j <= 3)) isValid = true;
			else if (i == 2) isValid = true;
            if (isValid)
            {
				char cellValue = board[i][j];
				if (cellValue == 0) cellValue = '.';
				cout << "| " << cellValue << " |";
            }
        }
		if (i == 0)
			cout << "\n            -----\n";
        if(i == 1)
			cout << "\n       ---------------\n";
        if(i == 2)
        cout << "\n  -------------------------\n";

    }
	cout << "\n\n----------------------------\n";
}