#include "InfinityTic-Tac-Toe.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std; 

Infinity_Board::Infinity_Board() : Board(3, 3) {
   
    for (auto& row : board)
        for (auto& cell : row)
            cell = 0 ;
}
bool Infinity_Board::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int symbol = move->get_symbol();

    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0) {
        return false; 
    }

   
    board[x][y] = symbol;

    move_history.push({ x, y });

   
    n_moves++;

    if (move_history.size() > 3) {
        pair<int, int> oldest_move = move_history.front();
        move_history.pop();

        int old_x = oldest_move.first;
        int old_y = oldest_move.second;

        board[old_x][old_y] = 0;
    }

    return true;
}