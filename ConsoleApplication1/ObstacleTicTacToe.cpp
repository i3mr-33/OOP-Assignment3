//#include "ObstacleTicTacToe.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <algorithm>
//
//using namespace std;
//
//ObstacleTicTacToe_Board::ObstacleTicTacToe_Board() : Board(6, 6) {
//    for (auto& row : board)
//        for (auto& cell : row)
//            cell = 0;
//}
//
//bool ObstacleTicTacToe_Board::update_board(Move<int>* move) {
//    int x = move->get_x();
//    int y = move->get_y();
//    int number = move->get_symbol();
//
//    // Validate coordinates
//    if (x < 0 || x >= rows || y < 0 || y >= columns) {
//        cout << "Invalid coordinates! Please use 0-2 for both x and y.\n";
//        return false;
//    }
//
//    // Check if cell is empty
//    if (board[x][y] != 0) {
//        cout << "Cell (" << x << ", " << y << ") is already occupied!\n";
//        return false;
//    }
//
//    // Check if number is valid and available
//    bool is_player1 = (number % 2 == 1); // Odd numbers for player 1
//    if (!is_number_available(number, is_player1)) {
//        cout << "Number " << number << " is not available for this player!\n";
//        return false;
//    }
//
//    // Apply the move
//    board[x][y] = number;
//    n_moves++;
//
//    // Remove the used number from available numbers
//    if (is_player1) {
//        available_odds.erase(remove(available_odds.begin(), available_odds.end(), number), available_odds.end());
//    }
//    else {
//        available_evens.erase(remove(available_evens.begin(), available_evens.end(), number), available_evens.end());
//    }
//
//    return true;
//}
//
//bool ObstacleTicTacToe_Board::is_win(Player<int>* player) {
//    // Check all rows, columns and diagonals for sum of 15
//    const int target_sum = 15;
//
//    // Check rows
//    for (int i = 0; i < rows; ++i) {
//        int sum = board[i][0] + board[i][1] + board[i][2];
//        if (sum == target_sum && board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
//            return true;
//        }
//    }
//
//    // Check columns
//    for (int j = 0; j < columns; ++j) {
//        int sum = board[0][j] + board[1][j] + board[2][j];
//        if (sum == target_sum && board[0][j] != 0 && board[1][j] != 0 && board[2][j] != 0) {
//            return true;
//        }
//    }
//
//    // Check diagonals
//    int diag1 = board[0][0] + board[1][1] + board[2][2];
//    int diag2 = board[0][2] + board[1][1] + board[2][0];
//
//    if ((diag1 == target_sum && board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) ||
//        (diag2 == target_sum && board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0)) {
//        return true;
//    }
//
//    return false;
//}
//
//bool ObstacleTicTacToe_Board::is_draw(Player<int>* player) {
//    return (n_moves == 36 && !is_win(player));
//}
//
//bool ObstacleTicTacToe_Board::game_is_over(Player<int>* player) {
//    return is_win(player) || is_draw(player);
//}
//
//
////--------------------------------------- NumericalTicTacToe_UI Implementation
//
//ObstacleTicTacToe_UI::ObstacleTicTacToe_UI()
//    : UI<int>("Welcome to Numerical Tic-Tac-Toe Game!", 3) {}
//
//Player<int>* ObstacleTicTacToe_UI::create_player(string& name, int symbol, PlayerType type) {
//    cout << "Creating " << (type == PlayerType::HUMAN ? "human" : "computer")
//        << " player: " << name << "\n";
//    return new Player<int>(name, symbol, type);
//}
//
//Move<int>* ObstacleTicTacToe_UI::get_move(Player<int>* player) {
//    int x, y, number;
//    bool is_player1 = (player->get_symbol() == 1); // Player 1 uses odd numbers
//
//    if (player->get_type() == PlayerType::HUMAN) {
//        
//    }
//    else { // COMPUTER player
//       
//    }
//
//    return new Move<int>(x, y, number);
//}
