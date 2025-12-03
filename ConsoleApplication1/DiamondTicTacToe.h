#ifndef DiamondTicTacToe_H
#define DiamondTicTacToe_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

//====================== DiamondTicTacToe_Board Class ======================
class DiamondTicTacToe_Board : public Board<char> {
private:
    char blank_symbol = '.';
    int last_move_x = -1;
    int last_move_y = -1; 
    char last_move_symbol = ' ';

public:
    DiamondTicTacToe_Board();

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool is_valid_cell(int x, int y) const;  

private:
    bool check_line(int x, int y, char sym, int dx, int dy, int required_length);
    bool check_double_win_for_last_move();
};

//====================== DiamondTicTacToe_UI Class ======================
class DiamondTicTacToe_UI : public UI<char> {
public:
    DiamondTicTacToe_UI();
    ~DiamondTicTacToe_UI();

    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    Move<char>* get_move(Player<char>* player) override;
    void display_board_matrix(const vector<vector<char>>& matrix) const override;
};

#endif // DiamondTicTacToe_H